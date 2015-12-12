#if 1
if (m->data && (status & HOST_RX_OWNED))
#else
		    if (m->data)    /* always dump regardless of valid RX
				     * data */
#endif
		    {
			dp = (u_int32_t *) OS_phystov((void *) (le32_to_cpu(m->data)));
			if (len >= 0x10)
			    pr_info("    %x[%x]: %08X %08X %08X %08x\n", (u_int32_t) dp, len,
				    *dp, *(dp + 1), *(dp + 2), *(dp + 3));
			else if (len >= 0x08)
			    pr_info("    %x[%x]: %08X %08X\n", (u_int32_t) dp, len,
				    *dp, *(dp + 1));
			else
			    pr_info("    %x[%x]: %08X\n", (u_int32_t) dp, len, *dp);
		    }
