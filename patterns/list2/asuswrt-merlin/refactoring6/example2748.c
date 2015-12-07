if ((CHIPID(sih->chip) == BCM4335_CHIP_ID) ||
	(CHIPID(sih->chip) == BCM4345_CHIP_ID) ||
#ifndef BCM4350_FPGA
	BCM4350_CHIP(sih->chip) ||
#endif
	0) {
		si_gci_chipctrl_overrides(osh, sih, pvars);
	}
