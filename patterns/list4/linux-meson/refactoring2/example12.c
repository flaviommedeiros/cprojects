#ifndef DEBUG_SOF
if (gintsts.d32 != DWC_SOF_INTR_MASK)
#endif
			DWC_DEBUGPL(DBG_HCD,
				    "DWC OTG HCD Interrupt Detected gintsts&gintmsk=0x%08x\n",
				    gintsts.d32);
