if((syscall == __NR_wait4)
#ifdef __NR_waitpid
	   || (syscall == __NR_waitpid)
#endif
	){
		debugger_wait(&parent, (int *) arg2, arg3, parent_syscall,
			      parent_normal_return, parent_wait_return);
	}
	else ptrace(PTRACE_SYSCALL, pid, 0, 0);
