#ifdef module_param_array
if (num_LLIPort > bd) {
#endif
			adapter->lli_port = LLIPort[bd];
			if (adapter->lli_port) {
				igb_validate_option(&adapter->lli_port, &opt,
				        adapter);
			} else {
				DPRINTK(PROBE, INFO, "%s turned off\n",
					opt.name);
			}
#ifdef module_param_array
		} else {
			adapter->lli_port = opt.def;
		}
