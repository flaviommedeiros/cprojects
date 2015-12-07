#ifndef CONFIG_DEBUG_BFIN_NO_KERN_HWTRACE
if (trapnr == VEC_CPLB_I_M || trapnr == VEC_CPLB_M)
			verbose_printk(KERN_NOTICE "No trace since you do not have "
			       "CONFIG_DEBUG_BFIN_NO_KERN_HWTRACE enabled\n\n");
		else
#endif
			dump_bfin_trace_buffer();
