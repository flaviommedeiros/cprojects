switch (actionid) {
	case IOV_GVAL(IOV_INTR):
		int_val = (int32)bus->intr;
		bcopy(&int_val, arg, val_size);
		break;

	case IOV_SVAL(IOV_INTR):
		bus->intr = bool_val;
		bus->intdis = FALSE;
		if (bus->dhd->up) {
			if (bus->intr) {
				DHD_INTR(("%s: enable SDIO device interrupts\n", __FUNCTION__));
				bcmsdh_intr_enable(bus->sdh);
			} else {
				DHD_INTR(("%s: disable SDIO interrupts\n", __FUNCTION__));
				bcmsdh_intr_disable(bus->sdh);
			}
		}
		break;

	case IOV_GVAL(IOV_POLLRATE):
		int_val = (int32)bus->pollrate;
		bcopy(&int_val, arg, val_size);
		break;

	case IOV_SVAL(IOV_POLLRATE):
		bus->pollrate = (uint)int_val;
		bus->poll = (bus->pollrate != 0);
		break;

	case IOV_GVAL(IOV_IDLETIME):
		int_val = bus->idletime;
		bcopy(&int_val, arg, val_size);
		break;

	case IOV_SVAL(IOV_IDLETIME):
		if ((int_val < 0) && (int_val != DHD_IDLE_IMMEDIATE)) {
			bcmerror = BCME_BADARG;
		} else {
			bus->idletime = int_val;
		}
		break;

	case IOV_GVAL(IOV_IDLECLOCK):
		int_val = (int32)bus->idleclock;
		bcopy(&int_val, arg, val_size);
		break;

	case IOV_SVAL(IOV_IDLECLOCK):
		bus->idleclock = int_val;
		break;

	case IOV_GVAL(IOV_SD1IDLE):
		int_val = (int32)sd1idle;
		bcopy(&int_val, arg, val_size);
		break;

	case IOV_SVAL(IOV_SD1IDLE):
		sd1idle = bool_val;
		break;


	case IOV_SVAL(IOV_MEMBYTES):
	case IOV_GVAL(IOV_MEMBYTES):
	{
		uint32 address;
		uint size, dsize;
		uint8 *data;

		bool set = (actionid == IOV_SVAL(IOV_MEMBYTES));

		ASSERT(plen >= 2*sizeof(int));

		address = (uint32)int_val;
		bcopy((char *)params + sizeof(int_val), &int_val, sizeof(int_val));
		size = (uint)int_val;

		/* Do some validation */
		dsize = set ? plen - (2 * sizeof(int)) : len;
		if (dsize < size) {
			DHD_ERROR(("%s: error on %s membytes, addr 0x%08x size %d dsize %d\n",
			           __FUNCTION__, (set ? "set" : "get"), address, size, dsize));
			bcmerror = BCME_BADARG;
			break;
		}

		DHD_INFO(("%s: Request to %s %d bytes at address 0x%08x\n", __FUNCTION__,
		          (set ? "write" : "read"), size, address));

		/* check if CR4 */
		if (si_setcore(bus->sih, ARMCR4_CORE_ID, 0)) {
			/*
			 * If address is start of RAM (i.e. a downloaded image),
			 * store the reset instruction to be written in 0
			 */
			if (address == bus->dongle_ram_base) {
				bus->resetinstr = *(((uint32*)params) + 2);
			}
		} else {
		/* If we know about SOCRAM, check for a fit */
		if ((bus->orig_ramsize) &&
		    ((address > bus->orig_ramsize) || (address + size > bus->orig_ramsize)))
		{
			uint8 enable, protect, remap;
			si_socdevram(bus->sih, FALSE, &enable, &protect, &remap);
			if (!enable || protect) {
				DHD_ERROR(("%s: ramsize 0x%08x doesn't have %d bytes at 0x%08x\n",
					__FUNCTION__, bus->orig_ramsize, size, address));
				DHD_ERROR(("%s: socram enable %d, protect %d\n",
					__FUNCTION__, enable, protect));
				bcmerror = BCME_BADARG;
				break;
			}

			if (!REMAP_ENAB(bus) && (address >= SOCDEVRAM_ARM_ADDR)) {
				uint32 devramsize = si_socdevram_size(bus->sih);
				if ((address < SOCDEVRAM_ARM_ADDR) ||
					(address + size > (SOCDEVRAM_ARM_ADDR + devramsize))) {
					DHD_ERROR(("%s: bad address 0x%08x, size 0x%08x\n",
						__FUNCTION__, address, size));
					DHD_ERROR(("%s: socram range 0x%08x,size 0x%08x\n",
						__FUNCTION__, SOCDEVRAM_ARM_ADDR, devramsize));
					bcmerror = BCME_BADARG;
					break;
				}
				/* move it such that address is real now */
				address -= SOCDEVRAM_ARM_ADDR;
				address += SOCDEVRAM_BP_ADDR;
				DHD_INFO(("%s: Request to %s %d bytes @ Mapped address 0x%08x\n",
					__FUNCTION__, (set ? "write" : "read"), size, address));
			} else if (REMAP_ENAB(bus) && REMAP_ISADDR(bus, address) && remap) {
				/* Can not access remap region while devram remap bit is set
				 * ROM content would be returned in this case
				 */
				DHD_ERROR(("%s: Need to disable remap for address 0x%08x\n",
					__FUNCTION__, address));
				bcmerror = BCME_ERROR;
				break;
			}
		}
		}

		/* Generate the actual data pointer */
		data = set ? (uint8*)params + 2 * sizeof(int): (uint8*)arg;

		/* Call to do the transfer */
		bcmerror = dhdsdio_membytes(bus, set, address, data, size);

		break;
	}

	case IOV_GVAL(IOV_RAMSIZE):
		int_val = (int32)bus->ramsize;
		bcopy(&int_val, arg, val_size);
		break;

	case IOV_GVAL(IOV_RAMSTART):
		int_val = (int32)bus->dongle_ram_base;
		bcopy(&int_val, arg, val_size);
		break;

	case IOV_GVAL(IOV_SDIOD_DRIVE):
		int_val = (int32)dhd_sdiod_drive_strength;
		bcopy(&int_val, arg, val_size);
		break;

	case IOV_SVAL(IOV_SDIOD_DRIVE):
		dhd_sdiod_drive_strength = int_val;
		si_sdiod_drive_strength_init(bus->sih, bus->dhd->osh, dhd_sdiod_drive_strength);
		break;

	case IOV_SVAL(IOV_SET_DOWNLOAD_STATE):
		bcmerror = dhdsdio_download_state(bus, bool_val);
		break;

	case IOV_SVAL(IOV_SOCRAM_STATE):
		bcmerror = dhdsdio_download_state(bus, bool_val);
		break;

	case IOV_SVAL(IOV_VARS):
		bcmerror = dhdsdio_downloadvars(bus, arg, len);
		break;

	case IOV_GVAL(IOV_READAHEAD):
		int_val = (int32)dhd_readahead;
		bcopy(&int_val, arg, val_size);
		break;

	case IOV_SVAL(IOV_READAHEAD):
		if (bool_val && !dhd_readahead)
			bus->nextlen = 0;
		dhd_readahead = bool_val;
		break;

	case IOV_GVAL(IOV_SDRXCHAIN):
		int_val = (int32)bus->use_rxchain;
		bcopy(&int_val, arg, val_size);
		break;

	case IOV_SVAL(IOV_SDRXCHAIN):
		if (bool_val && !bus->sd_rxchain)
			bcmerror = BCME_UNSUPPORTED;
		else
			bus->use_rxchain = bool_val;
		break;
	case IOV_GVAL(IOV_ALIGNCTL):
		int_val = (int32)dhd_alignctl;
		bcopy(&int_val, arg, val_size);
		break;

	case IOV_SVAL(IOV_ALIGNCTL):
		dhd_alignctl = bool_val;
		break;

	case IOV_GVAL(IOV_SDALIGN):
		int_val = DHD_SDALIGN;
		bcopy(&int_val, arg, val_size);
		break;

#ifdef DHD_DEBUG
	case IOV_GVAL(IOV_VARS):
		if (bus->varsz < (uint)len)
			bcopy(bus->vars, arg, bus->varsz);
		else
			bcmerror = BCME_BUFTOOSHORT;
		break;
#endif /* DHD_DEBUG */

#ifdef DHD_DEBUG
	case IOV_GVAL(IOV_SDREG):
	{
		sdreg_t *sd_ptr;
		uint32 addr, size;

		sd_ptr = (sdreg_t *)params;

		addr = (uintptr)bus->regs + sd_ptr->offset;
		size = sd_ptr->func;
		int_val = (int32)bcmsdh_reg_read(bus->sdh, addr, size);
		if (bcmsdh_regfail(bus->sdh))
			bcmerror = BCME_SDIO_ERROR;
		bcopy(&int_val, arg, sizeof(int32));
		break;
	}

	case IOV_SVAL(IOV_SDREG):
	{
		sdreg_t *sd_ptr;
		uint32 addr, size;

		sd_ptr = (sdreg_t *)params;

		addr = (uintptr)bus->regs + sd_ptr->offset;
		size = sd_ptr->func;
		bcmsdh_reg_write(bus->sdh, addr, size, sd_ptr->value);
		if (bcmsdh_regfail(bus->sdh))
			bcmerror = BCME_SDIO_ERROR;
		break;
	}

	/* Same as above, but offset is not backplane (not SDIO core) */
	case IOV_GVAL(IOV_SBREG):
	{
		sdreg_t sdreg;
		uint32 addr, size;

		bcopy(params, &sdreg, sizeof(sdreg));

		addr = SI_ENUM_BASE + sdreg.offset;
		size = sdreg.func;
		int_val = (int32)bcmsdh_reg_read(bus->sdh, addr, size);
		if (bcmsdh_regfail(bus->sdh))
			bcmerror = BCME_SDIO_ERROR;
		bcopy(&int_val, arg, sizeof(int32));
		break;
	}

	case IOV_SVAL(IOV_SBREG):
	{
		sdreg_t sdreg;
		uint32 addr, size;

		bcopy(params, &sdreg, sizeof(sdreg));

		addr = SI_ENUM_BASE + sdreg.offset;
		size = sdreg.func;
		bcmsdh_reg_write(bus->sdh, addr, size, sdreg.value);
		if (bcmsdh_regfail(bus->sdh))
			bcmerror = BCME_SDIO_ERROR;
		break;
	}

	case IOV_GVAL(IOV_SDCIS):
	{
		*(char *)arg = 0;

		bcmstrcat(arg, "\nFunc 0\n");
		bcmsdh_cis_read(bus->sdh, 0x10, (uint8 *)arg + strlen(arg), SBSDIO_CIS_SIZE_LIMIT);
		bcmstrcat(arg, "\nFunc 1\n");
		bcmsdh_cis_read(bus->sdh, 0x11, (uint8 *)arg + strlen(arg), SBSDIO_CIS_SIZE_LIMIT);
		bcmstrcat(arg, "\nFunc 2\n");
		bcmsdh_cis_read(bus->sdh, 0x12, (uint8 *)arg + strlen(arg), SBSDIO_CIS_SIZE_LIMIT);
		break;
	}

	case IOV_GVAL(IOV_FORCEEVEN):
		int_val = (int32)forcealign;
		bcopy(&int_val, arg, val_size);
		break;

	case IOV_SVAL(IOV_FORCEEVEN):
		forcealign = bool_val;
		break;

	case IOV_GVAL(IOV_TXBOUND):
		int_val = (int32)dhd_txbound;
		bcopy(&int_val, arg, val_size);
		break;

	case IOV_SVAL(IOV_TXBOUND):
		dhd_txbound = (uint)int_val;
		break;

	case IOV_GVAL(IOV_RXBOUND):
		int_val = (int32)dhd_rxbound;
		bcopy(&int_val, arg, val_size);
		break;

	case IOV_SVAL(IOV_RXBOUND):
		dhd_rxbound = (uint)int_val;
		break;

	case IOV_GVAL(IOV_TXMINMAX):
		int_val = (int32)dhd_txminmax;
		bcopy(&int_val, arg, val_size);
		break;

	case IOV_SVAL(IOV_TXMINMAX):
		dhd_txminmax = (uint)int_val;
		break;

	case IOV_GVAL(IOV_SERIALCONS):
		int_val = dhd_serialconsole(bus, FALSE, 0, &bcmerror);
		if (bcmerror != 0)
			break;

		bcopy(&int_val, arg, val_size);
		break;

	case IOV_SVAL(IOV_SERIALCONS):
		dhd_serialconsole(bus, TRUE, bool_val, &bcmerror);
		break;



#endif /* DHD_DEBUG */


#ifdef SDTEST
	case IOV_GVAL(IOV_EXTLOOP):
		int_val = (int32)bus->ext_loop;
		bcopy(&int_val, arg, val_size);
		break;

	case IOV_SVAL(IOV_EXTLOOP):
		bus->ext_loop = bool_val;
		break;

	case IOV_GVAL(IOV_PKTGEN):
		bcmerror = dhdsdio_pktgen_get(bus, arg);
		break;

	case IOV_SVAL(IOV_PKTGEN):
		bcmerror = dhdsdio_pktgen_set(bus, arg);
		break;
#endif /* SDTEST */

#if defined(SDIO_CRC_ERROR_FIX)
	case IOV_GVAL(IOV_WATERMARK):
		int_val = (int32)watermark;
		bcopy(&int_val, arg, val_size);
		break;

	case IOV_SVAL(IOV_WATERMARK):
		watermark = (uint)int_val;
		watermark = (watermark > SBSDIO_WATERMARK_MASK) ? SBSDIO_WATERMARK_MASK : watermark;
		DHD_ERROR(("Setting watermark as 0x%x.\n", watermark));
		bcmsdh_cfg_write(bus->sdh, SDIO_FUNC_1, SBSDIO_WATERMARK, (uint8)watermark, NULL);
		break;

	case IOV_GVAL(IOV_MESBUSYCTRL):
		int_val = (int32)mesbusyctrl;
		bcopy(&int_val, arg, val_size);
		break;

	case IOV_SVAL(IOV_MESBUSYCTRL):
		mesbusyctrl = (uint)int_val;
		mesbusyctrl = (mesbusyctrl > SBSDIO_MESBUSYCTRL_MASK)
			? SBSDIO_MESBUSYCTRL_MASK : mesbusyctrl;
		DHD_ERROR(("Setting mesbusyctrl as 0x%x.\n", mesbusyctrl));
		bcmsdh_cfg_write(bus->sdh, SDIO_FUNC_1, SBSDIO_FUNC1_MESBUSYCTRL,
			((uint8)mesbusyctrl | 0x80), NULL);
		break;
#endif /* SDIO_CRC_ERROR_FIX */


	case IOV_GVAL(IOV_DONGLEISOLATION):
		int_val = bus->dhd->dongle_isolation;
		bcopy(&int_val, arg, val_size);
		break;

	case IOV_SVAL(IOV_DONGLEISOLATION):
		bus->dhd->dongle_isolation = bool_val;
		break;

	case IOV_SVAL(IOV_DEVRESET):
		DHD_TRACE(("%s: Called set IOV_DEVRESET=%d dongle_reset=%d busstate=%d\n",
		           __FUNCTION__, bool_val, bus->dhd->dongle_reset,
		           bus->dhd->busstate));

		ASSERT(bus->dhd->osh);
		/* ASSERT(bus->cl_devid); */

		dhd_bus_devreset(bus->dhd, (uint8)bool_val);

		break;
#ifdef SOFTAP
	case IOV_GVAL(IOV_FWPATH):
	{
		uint32  fw_path_len;

		fw_path_len = strlen(bus->fw_path);
		DHD_INFO(("[softap] get fwpath, l=%d\n", len));

		if (fw_path_len > len-1) {
			bcmerror = BCME_BUFTOOSHORT;
			break;
		}

		if (fw_path_len) {
			bcopy(bus->fw_path, arg, fw_path_len);
			((uchar*)arg)[fw_path_len] = 0;
		}
		break;
	}

	case IOV_SVAL(IOV_FWPATH):
		DHD_INFO(("[softap] set fwpath, idx=%d\n", int_val));

		switch (int_val) {
		case 1:
			bus->fw_path = fw_path; /* ordinary one */
			break;
		case 2:
			bus->fw_path = fw_path2;
			break;
		default:
			bcmerror = BCME_BADARG;
			break;
		}

		DHD_INFO(("[softap] new fw path: %s\n", (bus->fw_path[0] ? bus->fw_path : "NULL")));
		break;

#endif /* SOFTAP */
	case IOV_GVAL(IOV_DEVRESET):
		DHD_TRACE(("%s: Called get IOV_DEVRESET\n", __FUNCTION__));

		/* Get its status */
		int_val = (bool) bus->dhd->dongle_reset;
		bcopy(&int_val, arg, val_size);

		break;

	case IOV_GVAL(IOV_KSO):
		int_val = dhdsdio_sleepcsr_get(bus);
		bcopy(&int_val, arg, val_size);
		break;

	case IOV_GVAL(IOV_DEVCAP):
		int_val = dhdsdio_devcap_get(bus);
		bcopy(&int_val, arg, val_size);
		break;

	case IOV_SVAL(IOV_DEVCAP):
		dhdsdio_devcap_set(bus, (uint8) int_val);
		break;

#ifdef BCMSDIOH_TXGLOM
	case IOV_GVAL(IOV_TXGLOMSIZE):
		int_val = (int32)bus->glomsize;
		bcopy(&int_val, arg, val_size);
		break;

	case IOV_SVAL(IOV_TXGLOMSIZE):
		if (int_val > SDPCM_MAXGLOM_SIZE) {
			bcmerror = BCME_ERROR;
		} else {
			bus->glomsize = (uint)int_val;
		}
		break;
	case IOV_GVAL(IOV_TXGLOMMODE):
		int_val = (int32)bus->glom_mode;
		bcopy(&int_val, arg, val_size);
		break;

	case IOV_SVAL(IOV_TXGLOMMODE):
		if ((int_val != SDPCM_TXGLOM_CPY) && (int_val != SDPCM_TXGLOM_MDESC)) {
			bcmerror = BCME_RANGE;
		} else {
			if ((bus->glom_mode = bcmsdh_set_mode(bus->sdh, (uint)int_val)) != int_val)
				bcmerror = BCME_ERROR;
		}
		break;
#endif /* BCMSDIOH_TXGLOM */

	case IOV_SVAL(IOV_HANGREPORT):
		bus->dhd->hang_report = bool_val;
		DHD_ERROR(("%s: Set hang_report as %d\n", __FUNCTION__, bus->dhd->hang_report));
		break;

	case IOV_GVAL(IOV_HANGREPORT):
		int_val = (int32)bus->dhd->hang_report;
		bcopy(&int_val, arg, val_size);
		break;
	default:
		bcmerror = BCME_UNSUPPORTED;
		break;
	}
