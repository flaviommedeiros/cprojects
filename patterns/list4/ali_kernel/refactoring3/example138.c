switch (hw->mac.type) {
#ifndef CONFIG_IGB_VMDQ_NETDEV
			case e1000_82576:
				opt.arg.r.max = 2;
				break;
			case e1000_82575:
				if (adapter->vmdq_pools == 2)
					opt.arg.r.max = 3;
				if (adapter->vmdq_pools <= 2)
					break;
#endif
			default:
				opt.arg.r.max = 1;
				break;
			}
