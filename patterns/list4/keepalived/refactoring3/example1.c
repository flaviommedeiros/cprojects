switch (v->loadbalancing_kind) {
#ifdef _WITH_LVS_
		case IP_VS_CONN_F_MASQ:
			long_ret = 1;
			break;
		case IP_VS_CONN_F_DROUTE:
			long_ret = 2;
			break;
		case IP_VS_CONN_F_TUNNEL:
			long_ret = 3;
			break;
#endif
		}
