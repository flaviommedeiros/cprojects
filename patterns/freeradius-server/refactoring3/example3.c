switch (conf->proto) {
#ifdef WITH_TCP
	case IPPROTO_TCP:
		sockfd = fr_socket_client_tcp(NULL, &conf->server_ipaddr, conf->server_port, true);
		break;
#endif

	default:
	case IPPROTO_UDP:
		sockfd = fr_socket_client_udp(NULL, &conf->server_ipaddr, conf->server_port, true);
		break;
	}
