switch (vp->da->attr) {
		case PW_USER_NAME:
			if (vp->vp_length >= sizeof(ut.ut_name)) {
				memcpy(ut.ut_name, vp->vp_strvalue, sizeof(ut.ut_name));
			} else {
				strlcpy(ut.ut_name, vp->vp_strvalue, sizeof(ut.ut_name));
			}
			break;

		case PW_LOGIN_IP_HOST:
		case PW_FRAMED_IP_ADDRESS:
			framed_address = vp->vp_ipaddr;
				break;
#ifdef USER_PROCESS
		case PW_FRAMED_PROTOCOL:
			protocol = vp->vp_integer;
			break;
#endif
		case PW_NAS_IP_ADDRESS:
			nas_address = vp->vp_ipaddr;
			break;

		case PW_NAS_PORT:
			nas_port = vp->vp_integer;
			port_seen = true;
			break;

		case PW_ACCT_DELAY_TIME:
			delay = vp->vp_ipaddr;
			break;
		}
