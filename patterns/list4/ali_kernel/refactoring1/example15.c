if (num_LRO > bd) {
#endif
			unsigned int lro = LRO[bd];
			igb_validate_option(&lro, &opt, adapter);
			netdev->features |= lro ? NETIF_F_LRO : 0;
#ifdef module_param_array
		} else if (opt.def == OPTION_ENABLED) {
			netdev->features |= NETIF_F_LRO;
		}
#endif
