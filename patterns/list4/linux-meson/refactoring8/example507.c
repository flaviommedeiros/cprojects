static const struct user_regset aarch64_regsets[] = {
	[REGSET_GPR] = {
		.core_note_type = NT_PRSTATUS,
		.n = sizeof(struct user_pt_regs) / sizeof(u64),
		.size = sizeof(u64),
		.align = sizeof(u64),
		.get = gpr_get,
		.set = gpr_set
	},
	[REGSET_FPR] = {
		.core_note_type = NT_PRFPREG,
		.n = sizeof(struct user_fpsimd_state) / sizeof(u32),
		/*
		 * We pretend we have 32-bit registers because the fpsr and
		 * fpcr are 32-bits wide.
		 */
		.size = sizeof(u32),
		.align = sizeof(u32),
		.get = fpr_get,
		.set = fpr_set
	},
	[REGSET_TLS] = {
		.core_note_type = NT_ARM_TLS,
		.n = 1,
		.size = sizeof(void *),
		.align = sizeof(void *),
		.get = tls_get,
		.set = tls_set,
	},
#ifdef CONFIG_HAVE_HW_BREAKPOINT
	[REGSET_HW_BREAK] = {
		.core_note_type = NT_ARM_HW_BREAK,
		.n = sizeof(struct user_hwdebug_state) / sizeof(u32),
		.size = sizeof(u32),
		.align = sizeof(u32),
		.get = hw_break_get,
		.set = hw_break_set,
	},
	[REGSET_HW_WATCH] = {
		.core_note_type = NT_ARM_HW_WATCH,
		.n = sizeof(struct user_hwdebug_state) / sizeof(u32),
		.size = sizeof(u32),
		.align = sizeof(u32),
		.get = hw_break_get,
		.set = hw_break_set,
	},
#endif
};
