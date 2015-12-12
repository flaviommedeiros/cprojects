#ifdef CONFIG_X86_32
if (have_fpx_regs) {
		struct user_fxsr_struct fpx;

		err = copy_from_user(&fpx,
			&((struct _fpstate __user *)sc.fpstate)->_fxsr_env[0],
				     sizeof(struct user_fxsr_struct));
		if (err)
			return 1;

		err = convert_fxsr_from_user(&fpx, sc.fpstate);
		if (err)
			return 1;

		err = restore_fpx_registers(pid, (unsigned long *) &fpx);
		if (err < 0) {
			printk(KERN_ERR "copy_sc_from_user - "
			       "restore_fpx_registers failed, errno = %d\n",
			       -err);
			return 1;
		}
	} else
#endif
	{
		struct user_i387_struct fp;

		err = copy_from_user(&fp, sc.fpstate,
				     sizeof(struct user_i387_struct));
		if (err)
			return 1;

		err = restore_fp_registers(pid, (unsigned long *) &fp);
		if (err < 0) {
			printk(KERN_ERR "copy_sc_from_user - "
			       "restore_fp_registers failed, errno = %d\n",
			       -err);
			return 1;
		}
	}
