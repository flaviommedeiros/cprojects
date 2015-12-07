#if 1
if (snd_gf1_peek(gus, 0) == 0x55 && snd_gf1_peek(gus, 1) == 0xaa)
#else
	if (0)			/* ok.. for testing of 0k RAM */
#endif
	{
		snd_interwave_bank_sizes(gus, psizes);
		lmct = (psizes[3] << 24) | (psizes[2] << 16) |
		    (psizes[1] << 8) | psizes[0];
#if 0
		printk("lmct = 0x%08x\n", lmct);
#endif
		for (i = 0; i < ARRAY_SIZE(lmc); i++)
			if (lmct == lmc[i]) {
#if 0
				printk("found !!! %i\n", i);
#endif
				snd_gf1_write16(gus, SNDRV_GF1_GW_MEMORY_CONFIG, (snd_gf1_look16(gus, SNDRV_GF1_GW_MEMORY_CONFIG) & 0xfff0) | i);
				snd_interwave_bank_sizes(gus, psizes);
				break;
			}
		if (i >= ARRAY_SIZE(lmc) && !gus->gf1.enh_mode)
			 snd_gf1_write16(gus, SNDRV_GF1_GW_MEMORY_CONFIG, (snd_gf1_look16(gus, SNDRV_GF1_GW_MEMORY_CONFIG) & 0xfff0) | 2);
		for (i = 0; i < 4; i++) {
			gus->gf1.mem_alloc.banks_8[i].address =
			    gus->gf1.mem_alloc.banks_16[i].address = i << 22;
			gus->gf1.mem_alloc.banks_8[i].size =
			    gus->gf1.mem_alloc.banks_16[i].size = psizes[i] << 18;
			pages += psizes[i];
		}
	}
