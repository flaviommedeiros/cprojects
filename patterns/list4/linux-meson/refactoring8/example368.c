static const struct user_regset sh_regsets[] = {
	/*
	 * Format is:
	 *	PC, SR, SYSCALL,
	 *	R1 --> R63,
	 *	TR0 --> TR7,
	 */
	[REGSET_GENERAL] = {
		.core_note_type	= NT_PRSTATUS,
		.n		= ELF_NGREG,
		.size		= sizeof(long long),
		.align		= sizeof(long long),
		.get		= genregs_get,
		.set		= genregs_set,
	},

#ifdef CONFIG_SH_FPU
	[REGSET_FPU] = {
		.core_note_type	= NT_PRFPREG,
		.n		= sizeof(struct user_fpu_struct) /
				  sizeof(long long),
		.size		= sizeof(long long),
		.align		= sizeof(long long),
		.get		= fpregs_get,
		.set		= fpregs_set,
		.active		= fpregs_active,
	},
#endif
};
