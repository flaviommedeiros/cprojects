switch (vifc->vifc_flags) {
#ifdef CONFIG_IP_PIMSM
	case VIFF_REGISTER:
		/*
		 * Special Purpose VIF in PIM
		 * All the packets will be sent to the daemon
		 */
		if (mrt->mroute_reg_vif_num >= 0)
			return -EADDRINUSE;
		dev = ipmr_reg_vif(net, mrt);
		if (!dev)
			return -ENOBUFS;
		err = dev_set_allmulti(dev, 1);
		if (err) {
			unregister_netdevice(dev);
			dev_put(dev);
			return err;
		}
		break;
#endif
	case VIFF_TUNNEL:
		dev = ipmr_new_tunnel(net, vifc);
		if (!dev)
			return -ENOBUFS;
		err = dev_set_allmulti(dev, 1);
		if (err) {
			ipmr_del_tunnel(dev, vifc);
			dev_put(dev);
			return err;
		}
		break;

	case VIFF_USE_IFINDEX:
	case 0:
		if (vifc->vifc_flags == VIFF_USE_IFINDEX) {
			dev = dev_get_by_index(net, vifc->vifc_lcl_ifindex);
			if (dev && __in_dev_get_rtnl(dev) == NULL) {
				dev_put(dev);
				return -EADDRNOTAVAIL;
			}
		} else {
			dev = ip_dev_find(net, vifc->vifc_lcl_addr.s_addr);
		}
		if (!dev)
			return -EADDRNOTAVAIL;
		err = dev_set_allmulti(dev, 1);
		if (err) {
			dev_put(dev);
			return err;
		}
		break;
	default:
		return -EINVAL;
	}
