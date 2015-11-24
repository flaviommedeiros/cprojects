#ifdef WITH_TLS
if (tls) {
				home->port = PW_RADIUS_TLS_PORT;
			} else
#endif
			switch (home->type) {
			default:
				rad_assert(0);
				/* FALL-THROUGH */

			case HOME_TYPE_AUTH:
				home->port = PW_AUTH_UDP_PORT;
				break;

			case HOME_TYPE_ACCT:
				home->port = PW_ACCT_UDP_PORT;
				break;

			case HOME_TYPE_COA:
				home->port = PW_COA_UDP_PORT;
				break;
			}
