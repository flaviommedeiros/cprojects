#ifdef ENABLE_PF
if (!pf_c2c_test (c, &mi->context, "tap_c2c"))
				    {
				      msg (D_PF_DROPPED, "PF: client -> client[%s] packet dropped by TAP packet filter",
					   mi_prefix (mi));
				    }
				  else
#endif
				    {
				      multi_unicast (m, &c->c2.to_tun, mi);
				      register_activity (c, BLEN(&c->c2.to_tun));
				    }
