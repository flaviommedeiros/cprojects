if ((CHIPID(sih->chip) == BCM43602_CHIP_ID ||
	    CHIPID(sih->chip) == BCM43462_CHIP_ID) &&
#ifdef DONGLEBUILD
		(si_arm_clockratio(sih, 0) == 1) &&
#endif
		TRUE) {
		/* CR4 running on backplane_clk */
		return si_pmu_si_clock(sih, osh);	/* in [hz] units */
	}
