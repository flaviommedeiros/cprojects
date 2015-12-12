static const struct user_regset aarch32_ptrace_regsets[] = {
	[REGSET_GPR] = {
		.core_note_type = NT_PRSTATUS,
		.n = COMPAT_ELF_NGREG,
		.size = sizeof(compat_elf_greg_t),
		.align = sizeof(compat_elf_greg_t),
		.get = compat_gpr_get,
		.set = compat_gpr_set
	},
	[REGSET_FPR] = {
		.core_note_type = NT_ARM_VFP,
		.n = VFP_STATE_SIZE / sizeof(compat_ulong_t),
		.size = sizeof(compat_ulong_t),
		.align = sizeof(compat_ulong_t),
		.get = compat_vfp_get,
		.set = compat_vfp_set
	},
	[REGSET_TLS] = {
		.core_note_type = NT_ARM_TLS,
		.n = 1,
		.size = sizeof(compat_ulong_t),
		.align = sizeof(compat_ulong_t),
		.get = compat_tls_get,
		.set = compat_tls_set,
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
	[REGSET_SYSTEM_CALL] = {
		.core_note_type = NT_ARM_SYSTEM_CALL,
		.n = 1,
		.size = sizeof(int),
		.align = sizeof(int),
		.get = system_call_get,
		.set = system_call_set,
	},
};
