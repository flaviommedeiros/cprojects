#ifdef SIC_ISR
if (sic_status[0] & ivg->isrflag)
#else
		if (sic_status[(ivg->irqno - IVG7) / 32] & ivg->isrflag)
#endif
			return ivg->irqno;
