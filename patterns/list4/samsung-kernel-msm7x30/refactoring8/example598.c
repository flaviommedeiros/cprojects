int ieee80211_if_add(struct ieee80211_local *local, const char *name,
		     struct net_device **new_dev, enum nl80211_iftype type,
		     struct vif_params *params)
{
	struct net_device *ndev;
	struct ieee80211_sub_if_data *sdata = NULL;
	int ret, i;

	ASSERT_RTNL();

	ndev = alloc_netdev_mqs(sizeof(*sdata) + local->hw.vif_data_size,
				name, ieee80211_if_setup, local->hw.queues, 1);
	if (!ndev)
		return -ENOMEM;
	dev_net_set(ndev, wiphy_net(local->hw.wiphy));

	ndev->needed_headroom = local->tx_headroom +
				4*6 /* four MAC addresses */
				+ 2 + 2 + 2 + 2 /* ctl, dur, seq, qos */
				+ 6 /* mesh */
				+ 8 /* rfc1042/bridge tunnel */
				- ETH_HLEN /* ethernet hard_header_len */
				+ IEEE80211_ENCRYPT_HEADROOM;
	ndev->needed_tailroom = IEEE80211_ENCRYPT_TAILROOM;

	ret = dev_alloc_name(ndev, ndev->name);
	if (ret < 0)
		goto fail;

	ieee80211_assign_perm_addr(local, ndev, type);
	memcpy(ndev->dev_addr, ndev->perm_addr, ETH_ALEN);
	SET_NETDEV_DEV(ndev, wiphy_dev(local->hw.wiphy));

	/* don't use IEEE80211_DEV_TO_SUB_IF because it checks too much */
	sdata = netdev_priv(ndev);
	ndev->ieee80211_ptr = &sdata->wdev;
	memcpy(sdata->vif.addr, ndev->dev_addr, ETH_ALEN);
	memcpy(sdata->name, ndev->name, IFNAMSIZ);

	/* initialise type-independent data */
	sdata->wdev.wiphy = local->hw.wiphy;
	sdata->local = local;
	sdata->dev = ndev;
#ifdef CONFIG_INET
	sdata->arp_filter_state = true;
#endif

	for (i = 0; i < IEEE80211_FRAGMENT_MAX; i++)
		skb_queue_head_init(&sdata->fragments[i].skb_list);

	INIT_LIST_HEAD(&sdata->key_list);

	for (i = 0; i < IEEE80211_NUM_BANDS; i++) {
		struct ieee80211_supported_band *sband;
		sband = local->hw.wiphy->bands[i];
		sdata->rc_rateidx_mask[i] =
			sband ? (1 << sband->n_bitrates) - 1 : 0;
		if (sband)
			memcpy(sdata->rc_rateidx_mcs_mask[i],
			       sband->ht_cap.mcs.rx_mask,
			       sizeof(sdata->rc_rateidx_mcs_mask[i]));
		else
			memset(sdata->rc_rateidx_mcs_mask[i], 0,
			       sizeof(sdata->rc_rateidx_mcs_mask[i]));
	}

	/* setup type-dependent data */
	ieee80211_setup_sdata(sdata, type);

	if (params) {
		ndev->ieee80211_ptr->use_4addr = params->use_4addr;
		if (type == NL80211_IFTYPE_STATION)
			sdata->u.mgd.use_4addr = params->use_4addr;
	}

	ret = register_netdevice(ndev);
	if (ret)
		goto fail;

	mutex_lock(&local->iflist_mtx);
	list_add_tail_rcu(&sdata->list, &local->interfaces);
	mutex_unlock(&local->iflist_mtx);

	if (new_dev)
		*new_dev = ndev;

	return 0;

 fail:
	free_netdev(ndev);
	return ret;
}
