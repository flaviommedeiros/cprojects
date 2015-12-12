#ifdef DEBUG
if (gintsts.d32 != DWC_SOF_INTR_MASK)
#endif
		{
			DWC_DEBUGPL(DBG_HCD,
				    "DWC OTG HCD Finished Servicing Interrupts\n");
			DWC_DEBUGPL(DBG_HCDV, "DWC OTG HCD gintsts=0x%08x\n",
				    DWC_READ_REG32(&global_regs->gintsts));
			DWC_DEBUGPL(DBG_HCDV, "DWC OTG HCD gintmsk=0x%08x\n",
				    DWC_READ_REG32(&global_regs->gintmsk));
		}
