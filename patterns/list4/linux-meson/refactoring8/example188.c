struct wireless_dev *mwifiex_add_virtual_intf(struct wiphy *wiphy,
					      const char *name,
					      enum nl80211_iftype type,
					      u32 *flags,
					      struct vif_params *params)
{
	struct mwifiex_adapter *adapter = mwifiex_cfg80211_get_adapter(wiphy);
	struct mwifiex_private *priv;
	struct net_device *dev;
	void *mdev_priv;
	struct wireless_dev *wdev;

	if (!adapter)
		return ERR_PTR(-EFAULT);

	switch (type) {
	case NL80211_IFTYPE_UNSPECIFIED:
	case NL80211_IFTYPE_STATION:
	case NL80211_IFTYPE_ADHOC:
		priv = adapter->priv[MWIFIEX_BSS_TYPE_STA];
		if (priv->bss_mode) {
			wiphy_err(wiphy,
				  "cannot create multiple sta/adhoc ifaces\n");
			return ERR_PTR(-EINVAL);
		}

		wdev = kzalloc(sizeof(struct wireless_dev), GFP_KERNEL);
		if (!wdev)
			return ERR_PTR(-ENOMEM);

		wdev->wiphy = wiphy;
		priv->wdev = wdev;
		wdev->iftype = NL80211_IFTYPE_STATION;

		if (type == NL80211_IFTYPE_UNSPECIFIED)
			priv->bss_mode = NL80211_IFTYPE_STATION;
		else
			priv->bss_mode = type;

		priv->bss_type = MWIFIEX_BSS_TYPE_STA;
		priv->frame_type = MWIFIEX_DATA_FRAME_TYPE_ETH_II;
		priv->bss_priority = 0;
		priv->bss_role = MWIFIEX_BSS_ROLE_STA;
		priv->bss_num = 0;

		break;
	case NL80211_IFTYPE_AP:
		priv = adapter->priv[MWIFIEX_BSS_TYPE_UAP];

		if (priv->bss_mode) {
			wiphy_err(wiphy, "Can't create multiple AP interfaces");
			return ERR_PTR(-EINVAL);
		}

		wdev = kzalloc(sizeof(struct wireless_dev), GFP_KERNEL);
		if (!wdev)
			return ERR_PTR(-ENOMEM);

		priv->wdev = wdev;
		wdev->wiphy = wiphy;
		wdev->iftype = NL80211_IFTYPE_AP;

		priv->bss_type = MWIFIEX_BSS_TYPE_UAP;
		priv->frame_type = MWIFIEX_DATA_FRAME_TYPE_ETH_II;
		priv->bss_priority = 0;
		priv->bss_role = MWIFIEX_BSS_ROLE_UAP;
		priv->bss_started = 0;
		priv->bss_num = 0;
		priv->bss_mode = type;

		break;
	case NL80211_IFTYPE_P2P_CLIENT:
		priv = adapter->priv[MWIFIEX_BSS_TYPE_P2P];

		if (priv->bss_mode) {
			wiphy_err(wiphy, "Can't create multiple P2P ifaces");
			return ERR_PTR(-EINVAL);
		}

		wdev = kzalloc(sizeof(struct wireless_dev), GFP_KERNEL);
		if (!wdev)
			return ERR_PTR(-ENOMEM);

		priv->wdev = wdev;
		wdev->wiphy = wiphy;

		/* At start-up, wpa_supplicant tries to change the interface
		 * to NL80211_IFTYPE_STATION if it is not managed mode.
		 */
		wdev->iftype = NL80211_IFTYPE_P2P_CLIENT;
		priv->bss_mode = NL80211_IFTYPE_P2P_CLIENT;

		/* Setting bss_type to P2P tells firmware that this interface
		 * is receiving P2P peers found during find phase and doing
		 * action frame handshake.
		 */
		priv->bss_type = MWIFIEX_BSS_TYPE_P2P;

		priv->frame_type = MWIFIEX_DATA_FRAME_TYPE_ETH_II;
		priv->bss_priority = MWIFIEX_BSS_ROLE_STA;
		priv->bss_role = MWIFIEX_BSS_ROLE_STA;
		priv->bss_started = 0;
		priv->bss_num = 0;

		if (mwifiex_cfg80211_init_p2p_client(priv))
			return ERR_PTR(-EFAULT);

		break;
	default:
		wiphy_err(wiphy, "type not supported\n");
		return ERR_PTR(-EINVAL);
	}

	dev = alloc_netdev_mqs(sizeof(struct mwifiex_private *), name,
			       ether_setup, IEEE80211_NUM_ACS, 1);
	if (!dev) {
		wiphy_err(wiphy, "no memory available for netdevice\n");
		priv->bss_mode = NL80211_IFTYPE_UNSPECIFIED;
		return ERR_PTR(-ENOMEM);
	}

	mwifiex_init_priv_params(priv, dev);
	priv->netdev = dev;

	mwifiex_setup_ht_caps(&wiphy->bands[IEEE80211_BAND_2GHZ]->ht_cap, priv);
	if (adapter->is_hw_11ac_capable)
		mwifiex_setup_vht_caps(
			&wiphy->bands[IEEE80211_BAND_2GHZ]->vht_cap, priv);

	if (adapter->config_bands & BAND_A)
		mwifiex_setup_ht_caps(
			&wiphy->bands[IEEE80211_BAND_5GHZ]->ht_cap, priv);

	if ((adapter->config_bands & BAND_A) && adapter->is_hw_11ac_capable)
		mwifiex_setup_vht_caps(
			&wiphy->bands[IEEE80211_BAND_5GHZ]->vht_cap, priv);

	dev_net_set(dev, wiphy_net(wiphy));
	dev->ieee80211_ptr = priv->wdev;
	dev->ieee80211_ptr->iftype = priv->bss_mode;
	memcpy(dev->dev_addr, wiphy->perm_addr, ETH_ALEN);
	SET_NETDEV_DEV(dev, wiphy_dev(wiphy));

	dev->flags |= IFF_BROADCAST | IFF_MULTICAST;
	dev->watchdog_timeo = MWIFIEX_DEFAULT_WATCHDOG_TIMEOUT;
	dev->hard_header_len += MWIFIEX_MIN_DATA_HEADER_LEN;
	dev->ethtool_ops = &mwifiex_ethtool_ops;

	mdev_priv = netdev_priv(dev);
	*((unsigned long *) mdev_priv) = (unsigned long) priv;

	SET_NETDEV_DEV(dev, adapter->dev);

	/* Register network device */
	if (register_netdevice(dev)) {
		wiphy_err(wiphy, "cannot register virtual network device\n");
		free_netdev(dev);
		priv->bss_mode = NL80211_IFTYPE_UNSPECIFIED;
		return ERR_PTR(-EFAULT);
	}

	sema_init(&priv->async_sem, 1);

	dev_dbg(adapter->dev, "info: %s: Marvell 802.11 Adapter\n", dev->name);

#ifdef CONFIG_DEBUG_FS
	mwifiex_dev_debugfs_init(priv);
#endif
	return wdev;
}
