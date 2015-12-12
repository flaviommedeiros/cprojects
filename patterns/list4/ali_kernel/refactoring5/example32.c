#ifdef module_param_array
if (num_EEE > bd) {
#endif
				unsigned int eee = EEE[bd];
				igb_validate_option(&eee, &opt, adapter);
				adapter->flags |= eee ? IGB_FLAG_EEE : 0;
				if (eee)
					hw->dev_spec._82575.eee_disable = false;
				else
					hw->dev_spec._82575.eee_disable = true;

#ifdef module_param_array
			} else {
				adapter->flags |= opt.def ? IGB_FLAG_EEE : 0;
				if (adapter->flags & IGB_FLAG_EEE)
					hw->dev_spec._82575.eee_disable = false;
				else
					hw->dev_spec._82575.eee_disable = true;
			}
