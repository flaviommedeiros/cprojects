static double bench_algo_stage2(
	enum sha256_algos algo
)
{
	// Here, the gig is to safely run a piece of code that potentially
	// crashes. Unfortunately, the Right Way (tm) to do this is rather
	// heavily platform dependent :(

	double rate = -1.23457;

	#if defined(unix)

		// Make a pipe: [readFD, writeFD]
		int pfd[2];
		int r = pipe(pfd);
		if (r<0) {
			perror("pipe - failed to create pipe for --algo auto");
			exit(1);
		}

		// Make pipe non blocking
		set_non_blocking(pfd[0], 1);
		set_non_blocking(pfd[1], 1);

		// Don't allow a crashing child to kill the main process
		sighandler_t sr0 = signal(SIGPIPE, SIG_IGN);
		sighandler_t sr1 = signal(SIGPIPE, SIG_IGN);
		if (SIG_ERR==sr0 || SIG_ERR==sr1) {
			perror("signal - failed to edit signal mask for --algo auto");
			exit(1);
		}

		// Fork a child to do the actual benchmarking
		pid_t child_pid = fork();
		if (child_pid<0) {
			perror("fork - failed to create a child process for --algo auto");
			exit(1);
		}

		// Do the dangerous work in the child, knowing we might crash
		if (0==child_pid) {

			// TODO: some umask trickery to prevent coredumps

			// Benchmark this algorithm
			double r = bench_algo_stage3(algo);

			// We survived, send result to parent and bail
			int loop_count = 0;
			while (1) {
				ssize_t bytes_written = write(pfd[1], &r, sizeof(r));
				int try_again = (0==bytes_written || (bytes_written<0 && EAGAIN==errno));
				int success = (sizeof(r)==(size_t)bytes_written);

				if (success)
					break;

				if (!try_again) {
					perror("write - child failed to write benchmark result to pipe");
					exit(1);
				}

				if (5<loop_count) {
					applog(LOG_ERR, "child tried %d times to communicate with parent, giving up", loop_count);
					exit(1);
				}
				++loop_count;
				sleep(1);
			}
			exit(0);
		}

		// Parent waits for a result from child
		int loop_count = 0;
		while (1) {

			// Wait for child to die
			int status;
			int r = waitpid(child_pid, &status, WNOHANG);
			if ((child_pid==r) || (r<0 && ECHILD==errno)) {

				// Child died somehow. Grab result and bail
				double tmp;
				ssize_t bytes_read = read(pfd[0], &tmp, sizeof(tmp));
				if (sizeof(tmp)==(size_t)bytes_read)
					rate = tmp;
				break;

			} else if (r<0) {
				perror("bench_algo: waitpid failed. giving up.");
				exit(1);
			}

			// Give up on child after a ~60s
			if (60<loop_count) {
				kill(child_pid, SIGKILL);
				waitpid(child_pid, &status, 0);
				break;
			}

			// Wait a bit longer
			++loop_count;
			sleep(1);
		}

		// Close pipe
		r = close(pfd[0]);
		if (r<0) {
			perror("close - failed to close read end of pipe for --algo auto");
			exit(1);
		}
		r = close(pfd[1]);
		if (r<0) {
			perror("close - failed to close read end of pipe for --algo auto");
			exit(1);
		}

	#elif defined(WIN32)

		// Get handle to current exe
		HINSTANCE module = GetModuleHandle(0);
		if (!module) {
			applog(LOG_ERR, "failed to retrieve module handle");
			exit(1);
		}

		// Create a unique name
		char unique_name[33];
		snprintf(
			unique_name,
			sizeof(unique_name)-1,
			"bfgminer-%p",
			(void*)module
		);

		// Create and init a chunked of shared memory
		HANDLE map_handle = CreateFileMapping(
			INVALID_HANDLE_VALUE,   // use paging file
			NULL,                   // default security attributes
			PAGE_READWRITE,         // read/write access
			0,                      // size: high 32-bits
			4096,			// size: low 32-bits
			unique_name		// name of map object
		);
		if (NULL==map_handle) {
			applog(LOG_ERR, "could not create shared memory");
			exit(1);
		}

		void *shared_mem = MapViewOfFile(
			map_handle,	// object to map view of
			FILE_MAP_WRITE, // read/write access
			0,              // high offset:  map from
			0,              // low offset:   beginning
			0		// default: map entire file
		);
		if (NULL==shared_mem) {
			applog(LOG_ERR, "could not map shared memory");
			exit(1);
		}
		SetEnvironmentVariable("BFGMINER_SHARED_MEM", unique_name);
		CopyMemory(shared_mem, &rate, sizeof(rate));

		// Get path to current exe
		char cmd_line[256 + MAX_PATH];
		const size_t n = sizeof(cmd_line)-200;
		DWORD size = GetModuleFileName(module, cmd_line, n);
		if (0==size) {
			applog(LOG_ERR, "failed to retrieve module path");
			exit(1);
		}

		// Construct new command line based on that
		char buf[0x20];
		snprintf(buf, sizeof(buf), "%d", algo);
		SetEnvironmentVariable("BFGMINER_BENCH_ALGO", buf);

		// Launch a debug copy of BFGMiner
		STARTUPINFO startup_info;
		PROCESS_INFORMATION process_info;
		ZeroMemory(&startup_info, sizeof(startup_info));
		ZeroMemory(&process_info, sizeof(process_info));
		startup_info.cb = sizeof(startup_info);

		BOOL ok = CreateProcess(
			NULL,			// No module name (use command line)
			cmd_line,		// Command line
			NULL,			// Process handle not inheritable
			NULL,			// Thread handle not inheritable
			FALSE,			// Set handle inheritance to FALSE
			DEBUG_ONLY_THIS_PROCESS,// We're going to debug the child
			NULL,			// Use parent's environment block
			NULL,			// Use parent's starting directory
			&startup_info,		// Pointer to STARTUPINFO structure
			&process_info		// Pointer to PROCESS_INFORMATION structure
		);
		if (!ok) {
			applog(LOG_ERR, "CreateProcess failed with error %ld\n", (long)GetLastError() );
			exit(1);
		}

		// Debug the child (only clean way to catch exceptions)
		while (1) {

			// Wait for child to do something
			DEBUG_EVENT debug_event;
			ZeroMemory(&debug_event, sizeof(debug_event));

			BOOL ok = WaitForDebugEvent(&debug_event, 60 * 1000);
			if (!ok)
				break;

			// Decide if event is "normal"
			int go_on =
				CREATE_PROCESS_DEBUG_EVENT== debug_event.dwDebugEventCode	||
				CREATE_THREAD_DEBUG_EVENT == debug_event.dwDebugEventCode	||
				EXIT_THREAD_DEBUG_EVENT   == debug_event.dwDebugEventCode	||
				EXCEPTION_DEBUG_EVENT     == debug_event.dwDebugEventCode	||
				LOAD_DLL_DEBUG_EVENT      == debug_event.dwDebugEventCode	||
				OUTPUT_DEBUG_STRING_EVENT == debug_event.dwDebugEventCode	||
				UNLOAD_DLL_DEBUG_EVENT    == debug_event.dwDebugEventCode;
			if (!go_on)
				break;

			// Some exceptions are also "normal", apparently.
			if (EXCEPTION_DEBUG_EVENT== debug_event.dwDebugEventCode) {

				int go_on =
					EXCEPTION_BREAKPOINT== debug_event.u.Exception.ExceptionRecord.ExceptionCode;
				if (!go_on)
					break;
			}

			// If nothing unexpected happened, let child proceed
			ContinueDebugEvent(
				debug_event.dwProcessId,
				debug_event.dwThreadId,
				DBG_CONTINUE
			);
		}

		// Clean up child process
		TerminateProcess(process_info.hProcess, 1);
		CloseHandle(process_info.hProcess);
		CloseHandle(process_info.hThread);

		// Reap return value and cleanup
		CopyMemory(&rate, shared_mem, sizeof(rate));
		(void)UnmapViewOfFile(shared_mem);
		(void)CloseHandle(map_handle);

	#else

		// Not linux, not unix, not WIN32 ... do our best
		rate = bench_algo_stage3(algo);

	#endif // defined(unix)

	// Done
	return rate;
}
