switch ((sysloggerPid = fork_process()))
#endif
	{
		case -1:
			ereport(LOG,
					(errmsg("could not fork system logger: %m")));
			return 0;

#ifndef EXEC_BACKEND
		case 0:
			/* in postmaster child ... */
			/* Close the postmaster's sockets */
			ClosePostmasterPorts(true);

			/* Lose the postmaster's on-exit routines */
			on_exit_reset();

			/* Drop our connection to postmaster's shared memory, as well */
			dsm_detach_all();
			PGSharedMemoryDetach();

			/* do the work */
			SysLoggerMain(0, NULL);
			break;
#endif

		default:
			/* success, in postmaster */

			/* now we redirect stderr, if not done already */
			if (!redirection_done)
			{
#ifdef WIN32
				int			fd;
#endif

				/*
				 * Leave a breadcrumb trail when redirecting, in case the user
				 * forgets that redirection is active and looks only at the
				 * original stderr target file.
				 */
				ereport(LOG,
						(errmsg("redirecting log output to logging collector process"),
				errhint("Future log output will appear in directory \"%s\".",
						Log_directory)));

#ifndef WIN32
				fflush(stdout);
				if (dup2(syslogPipe[1], fileno(stdout)) < 0)
					ereport(FATAL,
							(errcode_for_file_access(),
							 errmsg("could not redirect stdout: %m")));
				fflush(stderr);
				if (dup2(syslogPipe[1], fileno(stderr)) < 0)
					ereport(FATAL,
							(errcode_for_file_access(),
							 errmsg("could not redirect stderr: %m")));
				/* Now we are done with the write end of the pipe. */
				close(syslogPipe[1]);
				syslogPipe[1] = -1;
#else

				/*
				 * open the pipe in binary mode and make sure stderr is binary
				 * after it's been dup'ed into, to avoid disturbing the pipe
				 * chunking protocol.
				 */
				fflush(stderr);
				fd = _open_osfhandle((intptr_t) syslogPipe[1],
									 _O_APPEND | _O_BINARY);
				if (dup2(fd, _fileno(stderr)) < 0)
					ereport(FATAL,
							(errcode_for_file_access(),
							 errmsg("could not redirect stderr: %m")));
				close(fd);
				_setmode(_fileno(stderr), _O_BINARY);

				/*
				 * Now we are done with the write end of the pipe.
				 * CloseHandle() must not be called because the preceding
				 * close() closes the underlying handle.
				 */
				syslogPipe[1] = 0;
#endif
				redirection_done = true;
			}

			/* postmaster will never write the file; close it */
			fclose(syslogFile);
			syslogFile = NULL;
			return (int) sysloggerPid;
	}
