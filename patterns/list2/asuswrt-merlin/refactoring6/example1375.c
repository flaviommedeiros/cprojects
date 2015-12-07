if ((si_is_sprom_available(sih) && srom[0] == 0xffff) ||
#ifdef BCMQT
			(si_is_sprom_available(sih) && sromrev == 0) ||
#endif
			(val & SPROM_OTPIN_USE)) {
			vp = base = mfgsromvars;

			if (defvarslen == 0) {
				BS_ERROR(("No nvm file, use generic default (for programming"
					" SPROM/OTP only)\n"));

				if (((CHIPID(sih->chip) == BCM4331_CHIP_ID) ||
					(CHIPID(sih->chip) == BCM43431_CHIP_ID)) &&
					(CHIPREV(sih->chiprev) < 3)) {

					defvarslen = srom_vars_len(defaultsromvars_4331);
					bcopy(defaultsromvars_4331, vp, defvarslen);
				} else if ((CHIPID(sih->chip) == BCM4350_CHIP_ID)) {
					/* For 4350 B1 and older */
					if (CHIPREV(sih->chiprev) <= 2) {
						defvarslen = srom_vars_len(defaultsromvars_4350);
						bcopy(defaultsromvars_4350, vp, defvarslen);
					} else {
						defvarslen = srom_vars_len(defaultsromvars_4350c0);
						bcopy(defaultsromvars_4350c0, vp, defvarslen);
					}
				} else if ((CHIPID(sih->chip) == BCM43569_CHIP_ID) ||
					(CHIPID(sih->chip) == BCM43570_CHIP_ID)) {
					defvarslen = srom_vars_len(defaultsromvars_4350c0);
					bcopy(defaultsromvars_4350c0, vp, defvarslen);
				} else if ((CHIPID(sih->chip) == BCM4354_CHIP_ID) ||
					(CHIPID(sih->chip) == BCM4356_CHIP_ID)) {
					if (CHIPREV(sih->chiprev) >= 1) {
						defvarslen = srom_vars_len(defaultsromvars_4354a1);
						bcopy(defaultsromvars_4354a1, vp, defvarslen);
					} else {
						defvarslen = srom_vars_len(defaultsromvars_4350c0);
						bcopy(defaultsromvars_4350c0, vp, defvarslen);
					}
				} else if (CHIPID(sih->chip) == BCM4335_CHIP_ID) {
					defvarslen = srom_vars_len(defaultsromvars_4335);
					bcopy(defaultsromvars_4335, vp, defvarslen);
				}
				else if (CHIPID(sih->chip) == BCM4345_CHIP_ID) {
					if (CHIPREV(sih->chiprev) <= 3) {
						defvarslen = srom_vars_len(defaultsromvars_4345);
						bcopy(defaultsromvars_4345, vp, defvarslen);
					} else {
						defvarslen = srom_vars_len(defaultsromvars_4345b0);
						bcopy(defaultsromvars_4345b0, vp, defvarslen);
					}
				} else if ((CHIPID(sih->chip) == BCM43602_CHIP_ID) ||
					(CHIPID(sih->chip) == BCM43462_CHIP_ID)) {
					defvarslen = srom_vars_len(defaultsromvars_43602);
					bcopy(defaultsromvars_43602, vp, defvarslen);
				} else {
					/* For 4311 A1 there is no signature to indicate that OTP is
					 * programmed, so can't really verify the OTP is
					 * unprogrammed or a bad OTP.
					 */
					if (CHIPID(sih->chip) == BCM4311_CHIP_ID) {
						const char *devid = "devid=0x4311";
						const size_t devid_strlen = strlen(devid);
						BS_ERROR(("setting the devid to be 4311\n"));
						bcopy(devid, vp, devid_strlen + 1);
						vp += devid_strlen + 1;
					}
					defvarslen = srom_vars_len(defaultsromvars_wltest);
					bcopy(defaultsromvars_wltest, vp, defvarslen);
				}
			} else {
				BS_ERROR(("Use nvm file as default\n"));
			}

			vp += defvarslen;
			/* add final null terminator */
			*vp++ = '\0';

			BS_ERROR(("Used %d bytes of defaultsromvars\n", defvarslen));
			goto varsdone;

		} else if ((((CHIPID(sih->chip) == BCM4331_CHIP_ID) ||
			(CHIPID(sih->chip) == BCM43431_CHIP_ID)) &&
			(CHIPREV(sih->chiprev) < 3)) || (CHIPID(sih->chip) == BCM4360_CHIP_ID) ||
			(CHIPID(sih->chip) == BCM43460_CHIP_ID) ||
			(CHIPID(sih->chip) == BCM43602_CHIP_ID) ||
			(CHIPID(sih->chip) == BCM43462_CHIP_ID) ||
			(CHIPID(sih->chip) == BCM4352_CHIP_ID)) {
			base = vp = mfgsromvars;

			if ((CHIPID(sih->chip) == BCM4360_CHIP_ID) ||
			    (CHIPID(sih->chip) == BCM43460_CHIP_ID) ||
			    (CHIPID(sih->chip) == BCM43602_CHIP_ID) ||
			    (CHIPID(sih->chip) == BCM43462_CHIP_ID) ||
			    (CHIPID(sih->chip) == BCM4352_CHIP_ID))
				BS_ERROR(("4360 BOOT w/o SPROM or OTP\n"));
			else
				BS_ERROR(("4331 BOOT w/o SPROM or OTP\n"));

			if (defvarslen == 0) {
				if ((CHIPID(sih->chip) == BCM43602_CHIP_ID) ||
					(CHIPID(sih->chip) == BCM43462_CHIP_ID)) {
					defvarslen = srom_vars_len(defaultsromvars_43602);
					bcopy(defaultsromvars_43602, vp, defvarslen);
				} else if ((CHIPID(sih->chip) == BCM4354_CHIP_ID) ||
					(CHIPID(sih->chip) == BCM4356_CHIP_ID)) {
					if (CHIPREV(sih->chiprev) >= 1) {
						defvarslen = srom_vars_len(defaultsromvars_4354a1);
						bcopy(defaultsromvars_4354a1, vp, defvarslen);
					} else {
						defvarslen = srom_vars_len(defaultsromvars_4350c0);
						bcopy(defaultsromvars_4350c0, vp, defvarslen);
					}
				} else {
					defvarslen = srom_vars_len(defaultsromvars_4331);
					bcopy(defaultsromvars_4331, vp, defvarslen);
				}
			}
			vp += defvarslen;
			*vp++ = '\0';
			goto varsdone;
		} else if ((CHIPID(sih->chip) == BCM4335_CHIP_ID) ||
			0) {
			base = vp = mfgsromvars;

			defvarslen = srom_vars_len(defaultsromvars_4335);
			bcopy(defaultsromvars_4335, vp, defvarslen);

			vp += defvarslen;
			*vp++ = '\0';
			goto varsdone;
		} else if (CHIPID(sih->chip) == BCM4345_CHIP_ID) {
			base = vp = mfgsromvars;
			if (CHIPREV(sih->chiprev) <= 3) {
				defvarslen = srom_vars_len(defaultsromvars_4345);
				bcopy(defaultsromvars_4345, vp, defvarslen);
			} else {
				defvarslen = srom_vars_len(defaultsromvars_4345b0);
				bcopy(defaultsromvars_4345b0, vp, defvarslen);
			}

			vp += defvarslen;
			*vp++ = '\0';
			goto varsdone;
		} else
#endif 
		{
			err = -1;
			goto errout;
		}
