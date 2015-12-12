if (type == PARAVIRT_PATCH(pv_cpu_ops.iret) ||
#ifdef CONFIG_X86_32
		 type == PARAVIRT_PATCH(pv_cpu_ops.irq_enable_sysexit) ||
#endif
		 type == PARAVIRT_PATCH(pv_cpu_ops.usergs_sysret32) ||
		 type == PARAVIRT_PATCH(pv_cpu_ops.usergs_sysret64))
		/* If operation requires a jmp, then jmp */
		ret = paravirt_patch_jmp(insnbuf, opfunc, addr, len);
	else
		/* Otherwise call the function; assume target could
		   clobber any caller-save reg */
		ret = paravirt_patch_call(insnbuf, opfunc, CLBR_ANY,
					  addr, clobbers, len);
