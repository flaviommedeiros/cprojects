#ifdef CONFIG_PCI
if (ctlp->BusType == isPCI)
			CtlMask = sPCIGetControllerIntStatus(ctlp);
		else
#endif
			CtlMask = sGetControllerIntStatus(ctlp);
