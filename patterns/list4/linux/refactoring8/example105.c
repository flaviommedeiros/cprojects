void iwl_mvm_rs_rate_init(struct iwl_mvm *mvm, struct ieee80211_sta *sta,
			  enum ieee80211_band band, bool init)
{
	int i, j;
	struct ieee80211_hw *hw = mvm->hw;
	struct ieee80211_sta_ht_cap *ht_cap = &sta->ht_cap;
	struct ieee80211_sta_vht_cap *vht_cap = &sta->vht_cap;
	struct iwl_mvm_sta *sta_priv = iwl_mvm_sta_from_mac80211(sta);
	struct iwl_lq_sta *lq_sta = &sta_priv->lq_sta;
	struct ieee80211_supported_band *sband;
	unsigned long supp; /* must be unsigned long for for_each_set_bit */

	/* clear all non-persistent lq data */
	memset(lq_sta, 0, offsetof(typeof(*lq_sta), pers));

	sband = hw->wiphy->bands[band];

	lq_sta->lq.sta_id = sta_priv->sta_id;

	for (j = 0; j < LQ_SIZE; j++)
		rs_rate_scale_clear_tbl_windows(mvm, &lq_sta->lq_info[j]);

	lq_sta->flush_timer = 0;
	lq_sta->last_tx = jiffies;

	IWL_DEBUG_RATE(mvm,
		       "LQ: *** rate scale station global init for station %d ***\n",
		       sta_priv->sta_id);
	/* TODO: what is a good starting rate for STA? About middle? Maybe not
	 * the lowest or the highest rate.. Could consider using RSSI from
	 * previous packets? Need to have IEEE 802.1X auth succeed immediately
	 * after assoc.. */

	lq_sta->missed_rate_counter = IWL_MVM_RS_MISSED_RATE_MAX;
	lq_sta->band = sband->band;
	/*
	 * active legacy rates as per supported rates bitmap
	 */
	supp = sta->supp_rates[sband->band];
	lq_sta->active_legacy_rate = 0;
	for_each_set_bit(i, &supp, BITS_PER_LONG)
		lq_sta->active_legacy_rate |= BIT(sband->bitrates[i].hw_value);

	/* TODO: should probably account for rx_highest for both HT/VHT */
	if (!vht_cap || !vht_cap->vht_supported)
		rs_ht_init(mvm, sta, lq_sta, ht_cap);
	else
		rs_vht_init(mvm, sta, lq_sta, vht_cap);

	lq_sta->max_legacy_rate_idx =
		rs_get_max_rate_from_mask(lq_sta->active_legacy_rate);
	lq_sta->max_siso_rate_idx =
		rs_get_max_rate_from_mask(lq_sta->active_siso_rate);
	lq_sta->max_mimo2_rate_idx =
		rs_get_max_rate_from_mask(lq_sta->active_mimo2_rate);

	IWL_DEBUG_RATE(mvm,
		       "LEGACY=%lX SISO=%lX MIMO2=%lX VHT=%d LDPC=%d STBC=%d BFER=%d\n",
		       lq_sta->active_legacy_rate,
		       lq_sta->active_siso_rate,
		       lq_sta->active_mimo2_rate,
		       lq_sta->is_vht, lq_sta->ldpc, lq_sta->stbc_capable,
		       lq_sta->bfer_capable);
	IWL_DEBUG_RATE(mvm, "MAX RATE: LEGACY=%d SISO=%d MIMO2=%d\n",
		       lq_sta->max_legacy_rate_idx,
		       lq_sta->max_siso_rate_idx,
		       lq_sta->max_mimo2_rate_idx);

	/* These values will be overridden later */
	lq_sta->lq.single_stream_ant_msk =
		first_antenna(iwl_mvm_get_valid_tx_ant(mvm));
	lq_sta->lq.dual_stream_ant_msk = ANT_AB;

	/* as default allow aggregation for all tids */
	lq_sta->tx_agg_tid_en = IWL_AGG_ALL_TID;
	lq_sta->is_agg = 0;
#ifdef CONFIG_IWLWIFI_DEBUGFS
	iwl_mvm_reset_frame_stats(mvm);
#endif
	rs_initialize_lq(mvm, sta, lq_sta, band, init);
}
