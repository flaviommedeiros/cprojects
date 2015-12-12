static const struct net_device_ops sky2_netdev_ops[2] = {
  {
	.ndo_open		= sky2_open,
	.ndo_stop		= sky2_close,
	.ndo_start_xmit		= sky2_xmit_frame,
	.ndo_do_ioctl		= sky2_ioctl,
	.ndo_validate_addr	= eth_validate_addr,
	.ndo_set_mac_address	= sky2_set_mac_address,
	.ndo_set_rx_mode	= sky2_set_multicast,
	.ndo_change_mtu		= sky2_change_mtu,
	.ndo_fix_features	= sky2_fix_features,
	.ndo_set_features	= sky2_set_features,
	.ndo_tx_timeout		= sky2_tx_timeout,
	.ndo_get_stats64	= sky2_get_stats,
#ifdef CONFIG_NET_POLL_CONTROLLER
	.ndo_poll_controller	= sky2_netpoll,
#endif
  },
  {
	.ndo_open		= sky2_open,
	.ndo_stop		= sky2_close,
	.ndo_start_xmit		= sky2_xmit_frame,
	.ndo_do_ioctl		= sky2_ioctl,
	.ndo_validate_addr	= eth_validate_addr,
	.ndo_set_mac_address	= sky2_set_mac_address,
	.ndo_set_rx_mode	= sky2_set_multicast,
	.ndo_change_mtu		= sky2_change_mtu,
	.ndo_fix_features	= sky2_fix_features,
	.ndo_set_features	= sky2_set_features,
	.ndo_tx_timeout		= sky2_tx_timeout,
	.ndo_get_stats64	= sky2_get_stats,
  },
};
