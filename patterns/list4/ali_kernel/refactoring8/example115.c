static void mvs_hba_memory_dump(struct mvs_info *mvi, u32 tag,
				enum sas_protocol proto)
{
#if (_MV_DUMP > 1)
	u32 sz, w_ptr;
	u64 addr;
	struct mvs_slot_info *slot = &mvi->slot_info[tag];

	/*Delivery Queue */
	sz = MVS_CHIP_SLOT_SZ;
	w_ptr = slot->tx;
	addr = mvi->tx_dma;
	dev_printk(KERN_DEBUG, mvi->dev,
		"Delivery Queue Size=%04d , WRT_PTR=%04X\n", sz, w_ptr);
	dev_printk(KERN_DEBUG, mvi->dev,
		"Delivery Queue Base Address=0x%llX (PA)"
		"(tx_dma=0x%llX), Entry=%04d\n",
		addr, (unsigned long long)mvi->tx_dma, w_ptr);
	mvs_hexdump(sizeof(u32), (u8 *)(&mvi->tx[mvi->tx_prod]),
			(u32) mvi->tx_dma + sizeof(u32) * w_ptr);
	/*Command List */
	addr = mvi->slot_dma;
	dev_printk(KERN_DEBUG, mvi->dev,
		"Command List Base Address=0x%llX (PA)"
		"(slot_dma=0x%llX), Header=%03d\n",
		addr, (unsigned long long)slot->buf_dma, tag);
	dev_printk(KERN_DEBUG, mvi->dev, "Command Header[%03d]:\n", tag);
	/*mvs_cmd_hdr */
	mvs_hexdump(sizeof(struct mvs_cmd_hdr), (u8 *)(&mvi->slot[tag]),
		(u32) mvi->slot_dma + tag * sizeof(struct mvs_cmd_hdr));
	/*1.command table area */
	dev_printk(KERN_DEBUG, mvi->dev, "+---->Command Table :\n");
	mvs_hexdump(slot->cmd_size, (u8 *) slot->buf, (u32) slot->buf_dma);
	/*2.open address frame area */
	dev_printk(KERN_DEBUG, mvi->dev, "+---->Open Address Frame :\n");
	mvs_hexdump(MVS_OAF_SZ, (u8 *) slot->buf + slot->cmd_size,
				(u32) slot->buf_dma + slot->cmd_size);
	/*3.status buffer */
	mvs_hba_sb_dump(mvi, tag, proto);
	/*4.PRD table */
	dev_printk(KERN_DEBUG, mvi->dev, "+---->PRD table :\n");
	mvs_hexdump(MVS_CHIP_DISP->prd_size() * slot->n_elem,
		(u8 *) slot->buf + slot->cmd_size + MVS_OAF_SZ,
		(u32) slot->buf_dma + slot->cmd_size + MVS_OAF_SZ);
#endif
}
