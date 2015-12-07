#ifdef BCMPCIEDEV
if ((BUSTYPE(bustype) == SI_BUS) &&
	    ((CHIPID(sih->chip) == BCM43602_CHIP_ID) ||
	     (CHIPID(sih->chip) == BCM43462_CHIP_ID))) {
#else
	if (BUSTYPE(bustype) == PCI_BUS) {
#endif /* BCMPCIEDEV */
		uint16 *srom = NULL;
		void *ccregs = NULL;
		uint32 ccval = 0;

		if ((CHIPID(sih->chip) == BCM4331_CHIP_ID) ||
		    (CHIPID(sih->chip) == BCM43431_CHIP_ID) ||
		    (CHIPID(sih->chip) == BCM4360_CHIP_ID) ||
		    (CHIPID(sih->chip) == BCM43460_CHIP_ID) ||
		    (CHIPID(sih->chip) == BCM43526_CHIP_ID) ||
		    (CHIPID(sih->chip) == BCM43602_CHIP_ID) ||
		    (CHIPID(sih->chip) == BCM43462_CHIP_ID) ||
		    (CHIPID(sih->chip) == BCM4352_CHIP_ID)) {
			/* save current control setting */
			ccval = si_chipcontrl_read(sih);
		}

		if ((CHIPID(sih->chip) == BCM4331_CHIP_ID) ||
			(CHIPID(sih->chip) == BCM43431_CHIP_ID)) {
			/* Disable Ext PA lines to allow reading from SROM */
			si_chipcontrl_epa4331(sih, FALSE);
		} else if (((CHIPID(sih->chip) == BCM4360_CHIP_ID) ||
			(CHIPID(sih->chip) == BCM43460_CHIP_ID) ||
			(CHIPID(sih->chip) == BCM43602_CHIP_ID) ||
			(CHIPID(sih->chip) == BCM43462_CHIP_ID) ||
			(CHIPID(sih->chip) == BCM4352_CHIP_ID)) &&
			(CHIPREV(sih->chiprev) <= 2)) {
			si_chipcontrl_srom4360(sih, TRUE);
		}

		/* enable writes to the SPROM */
		if (sih->ccrev > 31) {
			if (BUSTYPE(sih->bustype) == SI_BUS)
				ccregs = (void *)SI_ENUM_BASE;
			else
				ccregs = (void *)((uint8 *)curmap + PCI_16KB0_CCREGS_OFFSET);
			srom = (uint16 *)((uint8 *)ccregs + CC_SROM_OTP);
			(void)srom_cc_cmd(sih, osh, ccregs, SRC_OP_WREN, 0, 0);
		} else {
			srom = (uint16 *)((uint8 *)curmap + PCI_BAR0_SPROM_OFFSET);
			val32 = OSL_PCI_READ_CONFIG(osh, PCI_SPROM_CONTROL, sizeof(uint32));
			val32 |= SPROM_WRITEEN;
			OSL_PCI_WRITE_CONFIG(osh, PCI_SPROM_CONTROL, sizeof(uint32), val32);
		}
		bcm_mdelay(WRITE_ENABLE_DELAY);
		/* write srom */
		if (sih->ccrev > 31) {
			if ((sih->cccaps & CC_CAP_SROM) == 0) {
				/* No srom support in this chip */
				BS_ERROR(("srom_write, invalid srom, skip\n"));
			} else
				(void)srom_cc_cmd(sih, osh, ccregs, SRC_OP_WRITE,
				                   byteoff/2, value);
		} else {
			W_REG(osh, &srom[byteoff/2], value);
		}
		bcm_mdelay(WRITE_WORD_DELAY);

		/* disable writes to the SPROM */
		if (sih->ccrev > 31) {
			(void)srom_cc_cmd(sih, osh, ccregs, SRC_OP_WRDIS, 0, 0);
		} else {
			OSL_PCI_WRITE_CONFIG(osh, PCI_SPROM_CONTROL, sizeof(uint32), val32 &
			                     ~SPROM_WRITEEN);
		}

		if ((CHIPID(sih->chip) == BCM4331_CHIP_ID) ||
		    (CHIPID(sih->chip) == BCM43431_CHIP_ID) ||
		    (CHIPID(sih->chip) == BCM4360_CHIP_ID) ||
		    (CHIPID(sih->chip) == BCM43460_CHIP_ID) ||
		    (CHIPID(sih->chip) == BCM43526_CHIP_ID) ||
		    (CHIPID(sih->chip) == BCM43602_CHIP_ID) ||
		    (CHIPID(sih->chip) == BCM43462_CHIP_ID) ||
		    (CHIPID(sih->chip) == BCM4352_CHIP_ID)) {
			/* Restore config after reading SROM */
			si_chipcontrl_restore(sih, ccval);
		}

	} else if (BUSTYPE(bustype) == PCMCIA_BUS) {
		/* enable writes to the SPROM */
		if (sprom_cmd_pcmcia(osh, SROM_WEN))
			goto done;
		bcm_mdelay(WRITE_ENABLE_DELAY);
		/* write srom */
		sprom_write_pcmcia(osh, (uint16)(byteoff/2), value);
		bcm_mdelay(WRITE_WORD_DELAY);

		/* disable writes to the SPROM */
		if (sprom_cmd_pcmcia(osh, SROM_WDS))
			goto done;
	} else if (BUSTYPE(bustype) == SI_BUS) {
#if defined(BCMUSBDEV)
		if (SPROMBUS == PCMCIA_BUS) {
			uint origidx;
			void *regs;
			bool wasup;

			origidx = si_coreidx(sih);
			regs = si_setcore(sih, PCMCIA_CORE_ID, 0);
			if (!regs)
				regs = si_setcore(sih, SDIOD_CORE_ID, 0);
			ASSERT(regs != NULL);

			if (!(wasup = si_iscoreup(sih)))
				si_core_reset(sih, 0, 0);

			rc = set_si_pcmcia_srom(sih, osh, regs, byteoff, &value, 2);

			if (!wasup)
				si_core_disable(sih, 0);

			si_setcoreidx(sih, origidx);
			goto done;
		}
#endif 
		goto done;
	} else {
		goto done;
	}

	bcm_mdelay(WRITE_ENABLE_DELAY);
	rc = 0;

done:
	return rc;
}
