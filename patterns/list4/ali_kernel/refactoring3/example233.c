switch (nvram->type) {
	case SYM_SYMBIOS_NVRAM:
		if (!(nvram->data.Symbios.flags & SYMBIOS_PARITY_ENABLE))
			np->rv_scntl0  &= ~0x0a;
		np->myaddr = nvram->data.Symbios.host_id & 0x0f;
		if (nvram->data.Symbios.flags & SYMBIOS_VERBOSE_MSGS)
			np->verbose += 1;
		if (nvram->data.Symbios.flags1 & SYMBIOS_SCAN_HI_LO)
			shost->reverse_ordering = 1;
		if (nvram->data.Symbios.flags2 & SYMBIOS_AVOID_BUS_RESET)
			np->usrflags |= SYM_AVOID_BUS_RESET;
		break;
	case SYM_TEKRAM_NVRAM:
		np->myaddr = nvram->data.Tekram.host_id & 0x0f;
		break;
#ifdef CONFIG_PARISC
	case SYM_PARISC_PDC:
		if (nvram->data.parisc.host_id != -1)
			np->myaddr = nvram->data.parisc.host_id;
		if (nvram->data.parisc.factor != -1)
			np->minsync = nvram->data.parisc.factor;
		if (nvram->data.parisc.width != -1)
			np->maxwide = nvram->data.parisc.width;
		switch (nvram->data.parisc.mode) {
			case 0: np->scsi_mode = SMODE_SE; break;
			case 1: np->scsi_mode = SMODE_HVD; break;
			case 2: np->scsi_mode = SMODE_LVD; break;
			default: break;
		}
#endif
	default:
		break;
	}
