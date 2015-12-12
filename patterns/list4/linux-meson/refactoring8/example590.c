struct sock_filter filter[] = {
		/* Grab the system call number */
		BPF_STMT(BPF_LD+BPF_W+BPF_ABS, syscall_nr),
		/* Jump table for the allowed syscalls */
		BPF_JUMP(BPF_JMP+BPF_JEQ+BPF_K, __NR_rt_sigreturn, 0, 1),
		BPF_STMT(BPF_RET+BPF_K, SECCOMP_RET_ALLOW),
#ifdef __NR_sigreturn
		BPF_JUMP(BPF_JMP+BPF_JEQ+BPF_K, __NR_sigreturn, 0, 1),
		BPF_STMT(BPF_RET+BPF_K, SECCOMP_RET_ALLOW),
#endif
		BPF_JUMP(BPF_JMP+BPF_JEQ+BPF_K, __NR_exit_group, 0, 1),
		BPF_STMT(BPF_RET+BPF_K, SECCOMP_RET_ALLOW),
		BPF_JUMP(BPF_JMP+BPF_JEQ+BPF_K, __NR_exit, 0, 1),
		BPF_STMT(BPF_RET+BPF_K, SECCOMP_RET_ALLOW),
		BPF_JUMP(BPF_JMP+BPF_JEQ+BPF_K, __NR_read, 1, 0),
		BPF_JUMP(BPF_JMP+BPF_JEQ+BPF_K, __NR_write, 3, 2),

		/* Check that read is only using stdin. */
		BPF_STMT(BPF_LD+BPF_W+BPF_ABS, syscall_arg(0)),
		BPF_JUMP(BPF_JMP+BPF_JEQ+BPF_K, STDIN_FILENO, 4, 0),
		BPF_STMT(BPF_RET+BPF_K, SECCOMP_RET_KILL),

		/* Check that write is only using stdout */
		BPF_STMT(BPF_LD+BPF_W+BPF_ABS, syscall_arg(0)),
		BPF_JUMP(BPF_JMP+BPF_JEQ+BPF_K, STDOUT_FILENO, 1, 0),
		/* Trap attempts to write to stderr */
		BPF_JUMP(BPF_JMP+BPF_JEQ+BPF_K, STDERR_FILENO, 1, 2),

		BPF_STMT(BPF_RET+BPF_K, SECCOMP_RET_ALLOW),
		BPF_STMT(BPF_RET+BPF_K, SECCOMP_RET_TRAP),
		BPF_STMT(BPF_RET+BPF_K, SECCOMP_RET_KILL),
	};
