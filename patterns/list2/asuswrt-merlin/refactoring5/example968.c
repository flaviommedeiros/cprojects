#ifdef CONFIG_64BIT
if (__is_compat_task(child)) {
			if (addr & (sizeof(int)-1))
				goto out_tsk;
			if ((addr = translate_usr_offset(addr)) < 0)
				goto out_tsk;
			DBG("sys_ptrace(POKEUSR, %d, %lx, %lx) addr %lx\n",
				pid, oaddr, odata, addr);
			if (addr >= PT_FR0 && addr <= PT_FR31 + 4) {
				/* Special case, fp regs are 64 bits anyway */
				*(unsigned int *) ((char *) task_regs(child) + addr) = data;
				ret = 0;
			}
			else if ((addr >= PT_GR1+4 && addr <= PT_GR31+4) ||
					addr == PT_IAOQ0+4 || addr == PT_IAOQ1+4 ||
					addr == PT_SAR+4) {
				/* Zero the top 32 bits */
				*(unsigned int *) ((char *) task_regs(child) + addr - 4) = 0;
				*(unsigned int *) ((char *) task_regs(child) + addr) = data;
				ret = 0;
			}
			goto out_tsk;
		}
		else
#endif
		{
			if ((addr & (sizeof(long)-1)) || (unsigned long) addr >= sizeof(struct pt_regs))
				goto out_tsk;
			if ((addr >= PT_GR1 && addr <= PT_GR31) ||
					addr == PT_IAOQ0 || addr == PT_IAOQ1 ||
					(addr >= PT_FR0 && addr <= PT_FR31 + 4) ||
					addr == PT_SAR) {
				*(unsigned long *) ((char *) task_regs(child) + addr) = data;
				ret = 0;
			}
			goto out_tsk;
		}
