#ifdef module_param_array
if (num_InterruptThrottleRate > bd) {
#endif
			unsigned int itr = InterruptThrottleRate[bd];

			switch (itr) {
			case 0:
				DPRINTK(PROBE, INFO, "%s turned off\n",
				        opt.name);
				if(hw->mac.type >= e1000_i350)
					adapter->dmac = IGB_DMAC_DISABLE;
				adapter->rx_itr_setting = itr;
				break;
			case 1:
				DPRINTK(PROBE, INFO, "%s set to dynamic mode\n",
					opt.name);
				adapter->rx_itr_setting = itr;
				break;
			case 3:
				DPRINTK(PROBE, INFO,
				        "%s set to dynamic conservative mode\n",
					opt.name);
				adapter->rx_itr_setting = itr;
				break;
			default:
				igb_validate_option(&itr, &opt, adapter);
				/* Save the setting, because the dynamic bits
				 * change itr.  In case of invalid user value,
				 * default to conservative mode, else need to
				 * clear the lower two bits because they are
				 * used as control */
				if (itr == 3) {
					adapter->rx_itr_setting = itr;
				} else {
					adapter->rx_itr_setting = 1000000000 /
					                          (itr * 256);
					adapter->rx_itr_setting &= ~3;
				}
				break;
			}
#ifdef module_param_array
		} else {
			adapter->rx_itr_setting = opt.def;
		}
