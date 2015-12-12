#if (LINUX_VERSION_CODE <= KERNEL_VERSION(2, 6, 35))
if (netdev->br_port)
#else   // (LINUX_VERSION_CODE <= KERNEL_VERSION(2, 6, 35))
		if (rcu_dereference(adapter->pnetdev->rx_handler_data))
#endif  // (LINUX_VERSION_CODE <= KERNEL_VERSION(2, 6, 35))
		{
			struct net_device *br_netdev;
#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,24))
			br_netdev = dev_get_by_name(CONFIG_BR_EXT_BRNAME);
#else	// (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,24))
			struct net *devnet = NULL;

#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,26))
			devnet = netdev->nd_net;
#else	// (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,26))
			devnet = dev_net(netdev);
#endif	// (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,26))

			br_netdev = dev_get_by_name(devnet, CONFIG_BR_EXT_BRNAME);
#endif	// (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,24))

			if (br_netdev) {
				memcpy(adapter->br_mac, br_netdev->dev_addr, ETH_ALEN);
				dev_put(br_netdev);
			} else
				printk("%s()-%d: dev_get_by_name(%s) failed!", __FUNCTION__, __LINE__, CONFIG_BR_EXT_BRNAME);
		}
