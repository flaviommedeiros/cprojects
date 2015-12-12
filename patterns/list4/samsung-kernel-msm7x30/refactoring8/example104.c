static int iwl_trans_pcie_tx(struct iwl_trans *trans, struct sk_buff *skb,
		struct iwl_device_cmd *dev_cmd, enum iwl_rxon_context_id ctx,
		u8 sta_id, u8 tid)
{
	struct iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	struct ieee80211_hdr *hdr = (struct ieee80211_hdr *)skb->data;
	struct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	struct iwl_tx_cmd *tx_cmd = (struct iwl_tx_cmd *) dev_cmd->payload;
	struct iwl_cmd_meta *out_meta;
	struct iwl_tx_queue *txq;
	struct iwl_queue *q;

	dma_addr_t phys_addr = 0;
	dma_addr_t txcmd_phys;
	dma_addr_t scratch_phys;
	u16 len, firstlen, secondlen;
	u8 wait_write_ptr = 0;
	u8 txq_id;
	bool is_agg = false;
	__le16 fc = hdr->frame_control;
	u8 hdr_len = ieee80211_hdrlen(fc);
	u16 __maybe_unused wifi_seq;

	/*
	 * Send this frame after DTIM -- there's a special queue
	 * reserved for this for contexts that support AP mode.
	 */
	if (info->flags & IEEE80211_TX_CTL_SEND_AFTER_DTIM) {
		txq_id = trans_pcie->mcast_queue[ctx];

		/*
		 * The microcode will clear the more data
		 * bit in the last frame it transmits.
		 */
		hdr->frame_control |=
			cpu_to_le16(IEEE80211_FCTL_MOREDATA);
	} else if (info->flags & IEEE80211_TX_CTL_TX_OFFCHAN)
		txq_id = IWL_AUX_QUEUE;
	else
		txq_id =
		    trans_pcie->ac_to_queue[ctx][skb_get_queue_mapping(skb)];

	/* aggregation is on for this <sta,tid> */
	if (info->flags & IEEE80211_TX_CTL_AMPDU) {
		WARN_ON(tid >= IWL_MAX_TID_COUNT);
		txq_id = trans_pcie->agg_txq[sta_id][tid];
		is_agg = true;
	}

	txq = &trans_pcie->txq[txq_id];
	q = &txq->q;

	spin_lock(&txq->lock);

	/* In AGG mode, the index in the ring must correspond to the WiFi
	 * sequence number. This is a HW requirements to help the SCD to parse
	 * the BA.
	 * Check here that the packets are in the right place on the ring.
	 */
#ifdef CONFIG_IWLWIFI_DEBUG
	wifi_seq = SEQ_TO_SN(le16_to_cpu(hdr->seq_ctrl));
	WARN_ONCE(is_agg && ((wifi_seq & 0xff) != q->write_ptr),
		  "Q: %d WiFi Seq %d tfdNum %d",
		  txq_id, wifi_seq, q->write_ptr);
#endif

	/* Set up driver data for this TFD */
	txq->skbs[q->write_ptr] = skb;
	txq->cmd[q->write_ptr] = dev_cmd;

	dev_cmd->hdr.cmd = REPLY_TX;
	dev_cmd->hdr.sequence = cpu_to_le16((u16)(QUEUE_TO_SEQ(txq_id) |
				INDEX_TO_SEQ(q->write_ptr)));

	/* Set up first empty entry in queue's array of Tx/cmd buffers */
	out_meta = &txq->meta[q->write_ptr];

	/*
	 * Use the first empty entry in this queue's command buffer array
	 * to contain the Tx command and MAC header concatenated together
	 * (payload data will be in another buffer).
	 * Size of this varies, due to varying MAC header length.
	 * If end is not dword aligned, we'll have 2 extra bytes at the end
	 * of the MAC header (device reads on dword boundaries).
	 * We'll tell device about this padding later.
	 */
	len = sizeof(struct iwl_tx_cmd) +
		sizeof(struct iwl_cmd_header) + hdr_len;
	firstlen = (len + 3) & ~3;

	/* Tell NIC about any 2-byte padding after MAC header */
	if (firstlen != len)
		tx_cmd->tx_flags |= TX_CMD_FLG_MH_PAD_MSK;

	/* Physical address of this Tx command's header (not MAC header!),
	 * within command buffer array. */
	txcmd_phys = dma_map_single(trans->dev,
				    &dev_cmd->hdr, firstlen,
				    DMA_BIDIRECTIONAL);
	if (unlikely(dma_mapping_error(trans->dev, txcmd_phys)))
		goto out_err;
	dma_unmap_addr_set(out_meta, mapping, txcmd_phys);
	dma_unmap_len_set(out_meta, len, firstlen);

	if (!ieee80211_has_morefrags(fc)) {
		txq->need_update = 1;
	} else {
		wait_write_ptr = 1;
		txq->need_update = 0;
	}

	/* Set up TFD's 2nd entry to point directly to remainder of skb,
	 * if any (802.11 null frames have no payload). */
	secondlen = skb->len - hdr_len;
	if (secondlen > 0) {
		phys_addr = dma_map_single(trans->dev, skb->data + hdr_len,
					   secondlen, DMA_TO_DEVICE);
		if (unlikely(dma_mapping_error(trans->dev, phys_addr))) {
			dma_unmap_single(trans->dev,
					 dma_unmap_addr(out_meta, mapping),
					 dma_unmap_len(out_meta, len),
					 DMA_BIDIRECTIONAL);
			goto out_err;
		}
	}

	/* Attach buffers to TFD */
	iwlagn_txq_attach_buf_to_tfd(trans, txq, txcmd_phys, firstlen, 1);
	if (secondlen > 0)
		iwlagn_txq_attach_buf_to_tfd(trans, txq, phys_addr,
					     secondlen, 0);

	scratch_phys = txcmd_phys + sizeof(struct iwl_cmd_header) +
				offsetof(struct iwl_tx_cmd, scratch);

	/* take back ownership of DMA buffer to enable update */
	dma_sync_single_for_cpu(trans->dev, txcmd_phys, firstlen,
			DMA_BIDIRECTIONAL);
	tx_cmd->dram_lsb_ptr = cpu_to_le32(scratch_phys);
	tx_cmd->dram_msb_ptr = iwl_get_dma_hi_addr(scratch_phys);

	IWL_DEBUG_TX(trans, "sequence nr = 0X%x\n",
		     le16_to_cpu(dev_cmd->hdr.sequence));
	IWL_DEBUG_TX(trans, "tx_flags = 0X%x\n", le32_to_cpu(tx_cmd->tx_flags));

	/* Set up entry for this TFD in Tx byte-count array */
	iwl_trans_txq_update_byte_cnt_tbl(trans, txq, le16_to_cpu(tx_cmd->len));

	dma_sync_single_for_device(trans->dev, txcmd_phys, firstlen,
			DMA_BIDIRECTIONAL);

	trace_iwlwifi_dev_tx(trans->dev,
			     &((struct iwl_tfd *)txq->tfds)[txq->q.write_ptr],
			     sizeof(struct iwl_tfd),
			     &dev_cmd->hdr, firstlen,
			     skb->data + hdr_len, secondlen);

	/* Tell device the write index *just past* this latest filled TFD */
	q->write_ptr = iwl_queue_inc_wrap(q->write_ptr, q->n_bd);
	iwl_txq_update_write_ptr(trans, txq);

	/*
	 * At this point the frame is "transmitted" successfully
	 * and we will get a TX status notification eventually,
	 * regardless of the value of ret. "ret" only indicates
	 * whether or not we should update the write pointer.
	 */
	if (iwl_queue_space(q) < q->high_mark) {
		if (wait_write_ptr) {
			txq->need_update = 1;
			iwl_txq_update_write_ptr(trans, txq);
		} else {
			iwl_stop_queue(trans, txq);
		}
	}
	spin_unlock(&txq->lock);
	return 0;
 out_err:
	spin_unlock(&txq->lock);
	return -1;
}
