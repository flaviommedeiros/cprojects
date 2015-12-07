#ifdef BCMPCIEDEV
if ((BUSTYPE(bustype) == SI_BUS) &&
	    ((CHIPID(sih->chip) == BCM43602_CHIP_ID) ||
	     (CHIPID(sih->chip) == BCM43570_CHIP_ID) ||
	     (CHIPID(sih->chip) == BCM43462_CHIP_ID))) {
#else
	if (BUSTYPE(bustype) == PCI_BUS) {
#endif /* BCMPCIEDEV */
		if (!curmap)
			return 1;

		if (si_is_sprom_available(sih)) {
			uint16 *srom;

			srom = (uint16 *)srom_offset(sih, curmap);
			if (srom == NULL)
				return 1;

			if (sprom_read_pci(osh, sih, srom, off, buf, nw, check_crc))
				return 1;
		}
#if !defined(BCMDONGLEHOST) && (defined(BCMNVRAMW) || defined(BCMNVRAMR))
		else if (!((BUSTYPE(bustype) == SI_BUS) &&
			((CHIPID(sih->chip) == BCM43602_CHIP_ID) ||
			(CHIPID(sih->chip) == BCM43462_CHIP_ID)))) {
			if (otp_read_pci(osh, sih, buf, nbytes))
				return 1;
		}
#endif /* !BCMDONGLEHOST && (BCMNVRAMW||BCMNVRAMR) */
	} else if (BUSTYPE(bustype) == PCMCIA_BUS) {
		for (i = 0; i < nw; i++) {
			if (sprom_read_pcmcia(osh, (uint16)(off + i), (uint16 *)(buf + i)))
				return 1;
		}
#ifdef BCMSPI
	} else if (BUSTYPE(bustype) == SPI_BUS) {
	                if (bcmsdh_cis_read(NULL, SDIO_FUNC_1, (uint8 *)buf, byteoff + nbytes) != 0)
				return 1;
#endif /* BCMSPI */
	} else if (BUSTYPE(bustype) == SI_BUS) {
#if defined(BCMUSBDEV)
		if (SPROMBUS == PCMCIA_BUS) {
			uint origidx;
			void *regs;
			int rc;
			bool wasup;

			/* Don't bother if we can't talk to SPROM */
			if (!si_is_sprom_available(sih))
				return 1;

			origidx = si_coreidx(sih);
			regs = si_setcore(sih, PCMCIA_CORE_ID, 0);
			if (!regs)
				regs = si_setcore(sih, SDIOD_CORE_ID, 0);
			ASSERT(regs != NULL);

			if (!(wasup = si_iscoreup(sih)))
				si_core_reset(sih, 0, 0);

			rc = get_si_pcmcia_srom(sih, osh, regs, byteoff, buf, nbytes, check_crc);

			if (!wasup)
				si_core_disable(sih, 0);

			si_setcoreidx(sih, origidx);
			return rc;
		}
#endif 

		return 1;
	} else {
		return 1;
	}

	return 0;
}
