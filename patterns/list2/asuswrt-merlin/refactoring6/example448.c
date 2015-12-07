if (!(fp->pc <= physical_mem_end
#if L1_CODE_LENGTH != 0
	    || (fp->pc >= L1_CODE_START &&
	        fp->pc <= (L1_CODE_START + L1_CODE_LENGTH))
#endif
	)) {
		if (current->mm) {
			fp->pc = current->mm->start_code;
		} else {
			printk(KERN_EMERG
				"I can't return to memory that doesn't exist"
				" - bad things happen\n");
			panic("Help - I've fallen and can't get up\n");
		}
	}
