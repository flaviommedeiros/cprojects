switch (this->type) {
		case RAD_LISTEN_PROXY:
			defined_proxy = true;
			break;

		case RAD_LISTEN_AUTH:
#ifdef WITH_ACCT
		case RAD_LISTEN_ACCT:
#endif
#ifdef WITH_COA
		case RAD_LISTEN_COA:
#endif
			sock = this->data;
			if (sock->my_ipaddr.af == AF_INET) has_v4 = true;
			if (sock->my_ipaddr.af == AF_INET6) has_v6 = true;
			break;

		default:
			break;
		}
