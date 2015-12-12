if (((!write && sd->use_rxchain) ||
#ifdef BCMSDIOH_TXGLOM
		(need_txglom && sd->txglom_mode == SDPCM_TXGLOM_MDESC) ||
#endif
		0) && (ttl_len >= blk_size)) {
		blk_num = ttl_len / blk_size;
		dma_len = blk_num * blk_size;
	} else {
		blk_num = 0;
		dma_len = 0;
	}
