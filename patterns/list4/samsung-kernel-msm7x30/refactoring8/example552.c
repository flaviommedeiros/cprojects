static int __used noinline
_sys_clone(nabi_no_regargs struct pt_regs regs)
{
	unsigned long clone_flags;
	unsigned long newsp;
	int __user *parent_tidptr, *child_tidptr;

	clone_flags = regs.regs[4];
	newsp = regs.regs[5];
	if (!newsp)
		newsp = regs.regs[29];
	parent_tidptr = (int __user *) regs.regs[6];
#ifdef CONFIG_32BIT
	/* We need to fetch the fifth argument off the stack.  */
	child_tidptr = NULL;
	if (clone_flags & (CLONE_CHILD_SETTID | CLONE_CHILD_CLEARTID)) {
		int __user *__user *usp = (int __user *__user *) regs.regs[29];
		if (regs.regs[2] == __NR_syscall) {
			if (get_user (child_tidptr, &usp[5]))
				return -EFAULT;
		}
		else if (get_user (child_tidptr, &usp[4]))
			return -EFAULT;
	}
#else
	child_tidptr = (int __user *) regs.regs[8];
#endif
	return do_fork(clone_flags, newsp, &regs, 0,
	               parent_tidptr, child_tidptr);
}
