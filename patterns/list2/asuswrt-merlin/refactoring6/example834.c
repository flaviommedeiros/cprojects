if ((CHIPID(sih->chip) == BCM4335_CHIP_ID) ||
#ifndef BCM4350_FPGA
	(CHIPID(sih->chip) == BCM4350_CHIP_ID) ||
#endif
	0) {
		si_gci_chipctrl_overrides(osh, sih, pvars);
	}
