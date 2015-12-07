#ifdef CONFIG_DEBUG_DOUBLEFAULT_PRINT
if (((long)fp->seqstat &  SEQSTAT_EXCAUSE) == VEC_UNCOV) {
		unsigned int cpu = raw_smp_processor_id();
		char buf[150];
		decode_address(buf, cpu_pda[cpu].retx_doublefault);
		printk(KERN_EMERG "While handling exception (EXCAUSE = 0x%x) at %s:\n",
			(unsigned int)cpu_pda[cpu].seqstat_doublefault & SEQSTAT_EXCAUSE, buf);
		decode_address(buf, cpu_pda[cpu].dcplb_doublefault_addr);
		printk(KERN_NOTICE "   DCPLB_FAULT_ADDR: %s\n", buf);
		decode_address(buf, cpu_pda[cpu].icplb_doublefault_addr);
		printk(KERN_NOTICE "   ICPLB_FAULT_ADDR: %s\n", buf);

		decode_address(buf, fp->retx);
		printk(KERN_NOTICE "The instruction at %s caused a double exception\n", buf);
	} else
#endif
	{
		dump_bfin_process(fp);
		dump_bfin_mem(fp);
		show_regs(fp);
		dump_bfin_trace_buffer();
	}
