#ifdef CONFIG_64BIT
if (!is_compat_task())
		audit_syscall_entry(regs->gr[20], regs->gr[26], regs->gr[25],
				    regs->gr[24], regs->gr[23]);
	else
#endif
		audit_syscall_entry(regs->gr[20] & 0xffffffff,
			regs->gr[26] & 0xffffffff,
			regs->gr[25] & 0xffffffff,
			regs->gr[24] & 0xffffffff,
			regs->gr[23] & 0xffffffff);
