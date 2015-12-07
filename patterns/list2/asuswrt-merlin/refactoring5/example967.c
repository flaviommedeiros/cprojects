#ifdef CONFIG_64BIT
if (__is_compat_task(child)) {
			unsigned int tmp;

			if (addr & (sizeof(int)-1))
				goto out_tsk;
			if ((addr = translate_usr_offset(addr)) < 0)
				goto out_tsk;

			tmp = *(unsigned int *) ((char *) task_regs(child) + addr);
			ret = put_user(tmp, (unsigned int *) data);
			DBG("sys_ptrace(PEEKUSR, %d, %lx, %lx) returning %ld, addr %lx, data %x\n",
				pid, oaddr, odata, ret, addr, tmp);
		}
		else
#endif
		{
			unsigned long tmp;

			if ((addr & (sizeof(long)-1)) || (unsigned long) addr >= sizeof(struct pt_regs))
				goto out_tsk;
			tmp = *(unsigned long *) ((char *) task_regs(child) + addr);
			ret = put_user(tmp, (unsigned long *) data);
		}
