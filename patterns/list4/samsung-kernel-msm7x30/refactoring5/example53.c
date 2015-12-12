#ifdef BCMSDIOH_TXGLOM
if (bus->glom_enable) {
		uint32 hwheader1, hwheader2;
		/* Software tag: channel, sequence number, data offset */
		swheader = ((SDPCM_CONTROL_CHANNEL << SDPCM_CHANNEL_SHIFT) & SDPCM_CHANNEL_MASK)
				| bus->tx_seq
				| ((doff << SDPCM_DOFFSET_SHIFT) & SDPCM_DOFFSET_MASK);
		htol32_ua_store(swheader, frame + SDPCM_FRAMETAG_LEN + SDPCM_HWEXT_LEN);
		htol32_ua_store(0, frame + SDPCM_FRAMETAG_LEN
			+ SDPCM_HWEXT_LEN + sizeof(swheader));

		hwheader1 = (msglen - SDPCM_FRAMETAG_LEN) | (1 << 24);
		hwheader2 = (len - (msglen)) << 16;
		htol32_ua_store(hwheader1, frame + SDPCM_FRAMETAG_LEN);
		htol32_ua_store(hwheader2, frame + SDPCM_FRAMETAG_LEN + 4);

		*(uint16*)frame = htol16(len);
		*(((uint16*)frame) + 1) = htol16(~(len));
	} else
#endif /* BCMSDIOH_TXGLOM */
	{
	/* Software tag: channel, sequence number, data offset */
	swheader = ((SDPCM_CONTROL_CHANNEL << SDPCM_CHANNEL_SHIFT) & SDPCM_CHANNEL_MASK)
	        | bus->tx_seq | ((doff << SDPCM_DOFFSET_SHIFT) & SDPCM_DOFFSET_MASK);
	htol32_ua_store(swheader, frame + SDPCM_FRAMETAG_LEN);
	htol32_ua_store(0, frame + SDPCM_FRAMETAG_LEN + sizeof(swheader));
	}
