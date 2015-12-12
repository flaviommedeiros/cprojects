#ifdef CONFIG_MMU
if (cpsr & MODE32_BIT) {
			struct mm_struct *mm = current->mm;
			/*
			 * 32-bit code can use the signal return page
			 * except when the MPU has protected the vectors
			 * page from PL0
			 */
			retcode = mm->context.sigpage + signal_return_offset +
				  (idx << 2) + thumb;
		} else
#endif
		{
			/*
			 * Ensure that the instruction cache sees
			 * the return code written onto the stack.
			 */
			flush_icache_range((unsigned long)rc,
					   (unsigned long)(rc + 2));

			retcode = ((unsigned long)rc) + thumb;
		}
