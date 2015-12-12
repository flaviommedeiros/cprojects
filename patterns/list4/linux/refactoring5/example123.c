#ifdef CONFIG_X86_32
if (have_fpx_regs) {
		struct user_fxsr_struct fpx;

		err = save_fpx_registers(pid, (unsigned long *) &fpx);
		if (err < 0){
			printk(KERN_ERR "copy_sc_to_user - save_fpx_registers "
			       "failed, errno = %d\n", err);
			return 1;
		}

		err = convert_fxsr_to_user(to_fp, &fpx);
		if (err)
			return 1;

		err |= __put_user(fpx.swd, &to_fp->status);
		err |= __put_user(X86_FXSR_MAGIC, &to_fp->magic);
		if (err)
			return 1;

		if (copy_to_user(&to_fp->_fxsr_env[0], &fpx,
				 sizeof(struct user_fxsr_struct)))
			return 1;
	} else
#endif
	{
		struct user_i387_struct fp;

		err = save_fp_registers(pid, (unsigned long *) &fp);
		if (copy_to_user(to_fp, &fp, sizeof(struct user_i387_struct)))
			return 1;
	}
