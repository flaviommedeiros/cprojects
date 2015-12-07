if (retaddr != 0 && retaddr <= (void*)physical_mem_end
#if L1_CODE_LENGTH != 0
	    /* FIXME: Copy the code out of L1 Instruction SRAM through dma
	       memcpy.  */
	    && !(retaddr >= (void*)L1_CODE_START
	         && retaddr < (void*)(L1_CODE_START + L1_CODE_LENGTH))
#endif
	) {
		int i = ((unsigned int)retaddr & 0xFFFFFFF0) - 32;
		unsigned short x = 0;
		for (; i < ((unsigned int)retaddr & 0xFFFFFFF0 ) + 32 ;
			i += 2) {
			if ( !(i & 0xF) )
				printk(KERN_EMERG "\n" KERN_EMERG
					"0x%08x: ", i);

			if (get_user(x, (unsigned short *)i))
				break;
#ifndef CONFIG_DEBUG_HWERR
			/* If one of the last few instructions was a STI
			 * it is likely that the error occured awhile ago
			 * and we just noticed
			 */
			if (x >= 0x0040 && x <= 0x0047 && i <= 0)
				panic("\n\nWARNING : You should reconfigure"
					" the kernel to turn on\n"
					" 'Hardware error interrupt"
					" debugging'\n"
					" The rest of this error"
					" is meanless\n");
#endif
			if ( i == (unsigned int)retaddr )
				printk("[%04x]", x);
			else
				printk(" %04x ", x);
		}
		printk("\n" KERN_EMERG "\n");
	} else
		printk(KERN_EMERG
			"Cannot look at the [PC] for it is"
			"in unreadable L1 SRAM - sorry\n");
