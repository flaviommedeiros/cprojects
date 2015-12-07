#ifdef CONFIG_MAC80211_DEBUGFS
if (in_atomic()) {
		list_add(&sta->list, &local->deleted_sta_list);
		queue_work(local->hw.workqueue, &local->sta_debugfs_add);
	} else
#endif
		finish_sta_info_free(local, sta);
