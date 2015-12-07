#ifdef CONFIG_64BIT
if (__is_compat_task(child)) {
			unsigned int tmp = (unsigned int)data;
			DBG("sys_ptrace(POKE%s, %d, %lx, %lx)\n",
				request == PTRACE_POKETEXT ? "TEXT" : "DATA",
				pid, oaddr, odata);
			addr &= 0xffffffffL;
			if (access_process_vm(child, addr, &tmp, sizeof(tmp), 1) == sizeof(tmp))
				goto out_tsk;
		}
		else
#endif
		{
			if (access_process_vm(child, addr, &data, sizeof(data), 1) == sizeof(data))
				goto out_tsk;
		}
