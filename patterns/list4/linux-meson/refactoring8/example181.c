void iwl_mvm_rs_rate_init(struct iwl_mvm *mvm, struct ieee80211_sta *sta,
			  enum ieee80211_band band)
{
	int i, j;
	struct ieee80211_hw *hw = mvm->hw;
	struct ieee80211_sta_ht_cap *ht_cap = &sta->ht_cap;
	struct iwl_mvm_sta *sta_priv;
	struct iwl_lq_sta *lq_sta;
	struct ieee80211_supported_band *sband;
	unsigned long supp; /* must be unsigned long for for_each_set_bit */

	sta_priv = (struct iwl_mvm_sta *)sta->drv_priv;
	lq_sta = &sta_priv->lq_sta;
	sband = hw->wiphy->bands[band];

	lq_sta->lq.sta_id = sta_priv->sta_id;

	for (j = 0; j < LQ_SIZE; j++)
		for (i = 0; i < IWL_RATE_COUNT; i++)
			rs_rate_scale_clear_window(&lq_sta->lq_info[j].win[i]);

	lq_sta->flush_timer = 0;
	lq_sta->supp_rates = sta->supp_rates[sband->band];
	for (j = 0; j < LQ_SIZE; j++)
		for (i = 0; i < IWL_RATE_COUNT; i++)
			rs_rate_scale_clear_window(&lq_sta->lq_info[j].win[i]);

	IWL_DEBUG_RATE(mvm,
		       "LQ: *** rate scale station global init for station %d ***\n",
		       sta_priv->sta_id);
	/* TODO: what is a good starting rate for STA? About middle? Maybe not
	 * the lowest or the highest rate.. Could consider using RSSI from
	 * previous packets? Need to have IEEE 802.1X auth succeed immediately
	 * after assoc.. */

	lq_sta->max_rate_idx = -1;
	lq_sta->missed_rate_counter = IWL_MISSED_RATE_MAX;
	lq_sta->is_green = rs_use_green(sta);
	lq_sta->band = sband->band;
	/*
	 * active legacy rates as per supported rates bitmap
	 */
	supp = sta->supp_rates[sband->band];
	lq_sta->active_legacy_rate = 0;
	for_each_set_bit(i, &supp, BITS_PER_LONG)
		lq_sta->active_legacy_rate |= BIT(sband->bitrates[i].hw_value);

	/*
	 * active_siso_rate mask includes 9 MBits (bit 5), and CCK (bits 0-3),
	 * supp_rates[] does not; shift to convert format, force 9 MBits off.
	 */
	lq_sta->active_siso_rate = ht_cap->mcs.rx_mask[0] << 1;
	lq_sta->active_siso_rate |= ht_cap->mcs.rx_mask[0] & 0x1;
	lq_sta->active_siso_rate &= ~((u16)0x2);
	lq_sta->active_siso_rate <<= IWL_FIRST_OFDM_RATE;

	/* Same here */
	lq_sta->active_mimo2_rate = ht_cap->mcs.rx_mask[1] << 1;
	lq_sta->active_mimo2_rate |= ht_cap->mcs.rx_mask[1] & 0x1;
	lq_sta->active_mimo2_rate &= ~((u16)0x2);
	lq_sta->active_mimo2_rate <<= IWL_FIRST_OFDM_RATE;

	lq_sta->active_mimo3_rate = ht_cap->mcs.rx_mask[2] << 1;
	lq_sta->active_mimo3_rate |= ht_cap->mcs.rx_mask[2] & 0x1;
	lq_sta->active_mimo3_rate &= ~((u16)0x2);
	lq_sta->active_mimo3_rate <<= IWL_FIRST_OFDM_RATE;

	IWL_DEBUG_RATE(mvm,
		       "SISO-RATE=%X MIMO2-RATE=%X MIMO3-RATE=%X\n",
		       lq_sta->active_siso_rate,
		       lq_sta->active_mimo2_rate,
		       lq_sta->active_mimo3_rate);

	/* These values will be overridden later */
	lq_sta->lq.single_stream_ant_msk =
		first_antenna(iwl_fw_valid_tx_ant(mvm->fw));
	lq_sta->lq.dual_stream_ant_msk =
		iwl_fw_valid_tx_ant(mvm->fw) &
		~first_antenna(iwl_fw_valid_tx_ant(mvm->fw));
	if (!lq_sta->lq.dual_stream_ant_msk) {
		lq_sta->lq.dual_stream_ant_msk = ANT_AB;
	} else if (num_of_ant(iwl_fw_valid_tx_ant(mvm->fw)) == 2) {
		lq_sta->lq.dual_stream_ant_msk =
			iwl_fw_valid_tx_ant(mvm->fw);
	}

	/* as default allow aggregation for all tids */
	lq_sta->tx_agg_tid_en = IWL_AGG_ALL_TID;
	lq_sta->drv = mvm;

	/* Set last_txrate_idx to lowest rate */
	lq_sta->last_txrate_idx = rate_lowest_index(sband, sta);
	if (sband->band == IEEE80211_BAND_5GHZ)
		lq_sta->last_txrate_idx += IWL_FIRST_OFDM_RATE;
	lq_sta->is_agg = 0;
#ifdef CONFIG_MAC80211_DEBUGFS
	lq_sta->dbg_fixed_rate = 0;
#endif

	rs_initialize_lq(mvm, sta, lq_sta, band);
}
