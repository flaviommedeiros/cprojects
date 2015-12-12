switch (cmd) {
	case SIOCSLICSETINTAGG:
		if (copy_from_user(data, rq->ifr_data, 28))
			return -EFAULT;
		intagg = data[0];
		dev_err(&dev->dev, "%s: set interrupt aggregation to %d\n",
			__func__, intagg);
		slic_intagg_set(adapter, intagg);
		return 0;

#ifdef SLIC_TRACE_DUMP_ENABLED
	case SIOCSLICTRACEDUMP:
		{
			u32 value;
			DBG_IOCTL("slic_ioctl  SIOCSLIC_TRACE_DUMP\n");

			if (copy_from_user(data, rq->ifr_data, 28)) {
				PRINT_ERROR
				    ("slic: copy_from_user FAILED getting \
				     initial simba param\n");
				return -EFAULT;
			}

			value = data[0];
			if (tracemon_request == SLIC_DUMP_DONE) {
				PRINT_ERROR
				    ("ATK Diagnostic Trace Dump Requested\n");
				tracemon_request = SLIC_DUMP_REQUESTED;
				tracemon_request_type = value;
				tracemon_timestamp = jiffies;
			} else if ((tracemon_request == SLIC_DUMP_REQUESTED) ||
				   (tracemon_request ==
				    SLIC_DUMP_IN_PROGRESS)) {
				PRINT_ERROR
				    ("ATK Diagnostic Trace Dump Requested but \
				     already in progress... ignore\n");
			} else {
				PRINT_ERROR
				    ("ATK Diagnostic Trace Dump Requested\n");
				tracemon_request = SLIC_DUMP_REQUESTED;
				tracemon_request_type = value;
				tracemon_timestamp = jiffies;
			}
			return 0;
		}
#endif
	case SIOCETHTOOL:
		ASSERT(adapter);
		if (copy_from_user(&ecmd, rq->ifr_data, sizeof(ecmd)))
			return -EFAULT;

		if (ecmd.cmd == ETHTOOL_GSET) {
			edata.supported = (SUPPORTED_10baseT_Half |
					   SUPPORTED_10baseT_Full |
					   SUPPORTED_100baseT_Half |
					   SUPPORTED_100baseT_Full |
					   SUPPORTED_Autoneg | SUPPORTED_MII);
			edata.port = PORT_MII;
			edata.transceiver = XCVR_INTERNAL;
			edata.phy_address = 0;
			if (adapter->linkspeed == LINK_100MB)
				edata.speed = SPEED_100;
			else if (adapter->linkspeed == LINK_10MB)
				edata.speed = SPEED_10;
			else
				edata.speed = 0;

			if (adapter->linkduplex == LINK_FULLD)
				edata.duplex = DUPLEX_FULL;
			else
				edata.duplex = DUPLEX_HALF;

			edata.autoneg = AUTONEG_ENABLE;
			edata.maxtxpkt = 1;
			edata.maxrxpkt = 1;
			if (copy_to_user(rq->ifr_data, &edata, sizeof(edata)))
				return -EFAULT;

		} else if (ecmd.cmd == ETHTOOL_SSET) {
			if (!capable(CAP_NET_ADMIN))
				return -EPERM;

			if (adapter->linkspeed == LINK_100MB)
				edata.speed = SPEED_100;
			else if (adapter->linkspeed == LINK_10MB)
				edata.speed = SPEED_10;
			else
				edata.speed = 0;

			if (adapter->linkduplex == LINK_FULLD)
				edata.duplex = DUPLEX_FULL;
			else
				edata.duplex = DUPLEX_HALF;

			edata.autoneg = AUTONEG_ENABLE;
			edata.maxtxpkt = 1;
			edata.maxrxpkt = 1;
			if ((ecmd.speed != edata.speed) ||
			    (ecmd.duplex != edata.duplex)) {
				u32 speed;
				u32 duplex;

				if (ecmd.speed == SPEED_10)
					speed = 0;
				else
					speed = PCR_SPEED_100;
				if (ecmd.duplex == DUPLEX_FULL)
					duplex = PCR_DUPLEX_FULL;
				else
					duplex = 0;
				slic_link_config(adapter, speed, duplex);
				slic_link_event_handler(adapter);
			}
		}
		return 0;
	default:
		return -EOPNOTSUPP;
	}
