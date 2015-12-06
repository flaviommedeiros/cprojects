switch (a.type)
	{
	case NA_LOOPBACK:
		Com_sprintf(s, sizeof(s), "loopback");
		break;
	case NA_BOT:
		Com_sprintf(s, sizeof(s), "bot");
		break;
	case NA_IP:
		// Port has to be returned along with ip address because of compatibility
		Com_sprintf(s, sizeof(s), "%i.%i.%i.%i:%hu",
		            a.ip[0], a.ip[1], a.ip[2], a.ip[3], BigShort(a.port));
		break;
#ifdef FEATURE_IPV6
	case NA_IP6:
	{
		// FIXME: add port for compatibility
		// (joining a server through the server browser)
		// Needs to be [ip]:port since : is a valid entry in ipv6
		struct sockaddr_storage sadr;

		memset(&sadr, 0, sizeof(sadr));
		NetadrToSockadr(&a, (struct sockaddr *) &sadr);
		Sys_SockaddrToString(s, sizeof(s), (struct sockaddr *) &sadr);
		break;
	}
	break;
#endif
	default:
		Com_Printf("NET_AdrToString: Unknown address type: %i\n", a.type);
		break;
	}
