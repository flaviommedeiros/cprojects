#ifdef CONFIG_64BIT
if (__is_compat_task(child)) {
			unsigned int tmp;

			addr &= 0xffffffffL;
			copied = access_process_vm(child, addr, &tmp, sizeof(tmp), 0);
			ret = -EIO;
			if (copied != sizeof(tmp))
				goto out_tsk;
			ret = put_user(tmp,(unsigned int *) data);
			DBG("sys_ptrace(PEEK%s, %d, %lx, %lx) returning %ld, data %x\n",
				request == PTRACE_PEEKTEXT ? "TEXT" : "DATA",
				pid, oaddr, odata, ret, tmp);
		}
		else
#endif
		{
			unsigned long tmp;

			copied = access_process_vm(child, addr, &tmp, sizeof(tmp), 0);
			ret = -EIO;
			if (copied != sizeof(tmp))
				goto out_tsk;
			ret = put_user(tmp,(unsigned long *) data);
		}
