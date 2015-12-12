static const struct user_regset s390_regsets[] = {
	[REGSET_GENERAL] = {
		.core_note_type = NT_PRSTATUS,
		.n = sizeof(s390_regs) / sizeof(long),
		.size = sizeof(long),
		.align = sizeof(long),
		.get = s390_regs_get,
		.set = s390_regs_set,
	},
	[REGSET_FP] = {
		.core_note_type = NT_PRFPREG,
		.n = sizeof(s390_fp_regs) / sizeof(long),
		.size = sizeof(long),
		.align = sizeof(long),
		.get = s390_fpregs_get,
		.set = s390_fpregs_set,
	},
#ifdef CONFIG_64BIT
	[REGSET_LAST_BREAK] = {
		.core_note_type = NT_S390_LAST_BREAK,
		.n = 1,
		.size = sizeof(long),
		.align = sizeof(long),
		.get = s390_last_break_get,
		.set = s390_last_break_set,
	},
#endif
	[REGSET_SYSTEM_CALL] = {
		.core_note_type = NT_S390_SYSTEM_CALL,
		.n = 1,
		.size = sizeof(unsigned int),
		.align = sizeof(unsigned int),
		.get = s390_system_call_get,
		.set = s390_system_call_set,
	},
};
