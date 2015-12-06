switch (this->type) {
		case RAD_LISTEN_AUTH:
			port_name = "radius";
			break;

#ifdef WITH_ACCOUNTING
		case RAD_LISTEN_ACCT:
			port_name = "radius-acct";
			break;
#endif

#ifdef WITH_PROXY
		case RAD_LISTEN_PROXY:
			/* leave it at zero */
			break;
#endif

#ifdef WITH_VMPS
		case RAD_LISTEN_VQP:
			sock->my_port = 1589;
			break;
#endif

#ifdef WITH_COMMAND_SOCKET
		case RAD_LISTEN_COMMAND:
			sock->my_port = PW_RADMIN_PORT;
			break;
#endif

#ifdef WITH_COA
		case RAD_LISTEN_COA:
			port_name = "radius-dynauth";
			break;
#endif

#ifdef WITH_DHCP
		case RAD_LISTEN_DHCP:
			port_name = "bootps";
			break;
#endif

		default:
			WARN("Internal sanity check failed in binding to socket.  Ignoring problem");
			return -1;
		}
