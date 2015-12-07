#ifdef CONFIG_COMPAT
if (test_thread_flag(TIF_32BIT)) {
		parent_tid_ptr = compat_ptr(regs->u_regs[UREG_I2]);
		child_tid_ptr = compat_ptr(regs->u_regs[UREG_I4]);
	} else
#endif
	{
		parent_tid_ptr = (int __user *) regs->u_regs[UREG_I2];
		child_tid_ptr = (int __user *) regs->u_regs[UREG_I4];
	}
