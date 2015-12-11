switch( type )
	{
	case SOCKET_LOOPBACK:
		return "loopback";

	case SOCKET_UDP:
		return "UDP";

#ifdef TCP_SUPPORT
	case SOCKET_TCP:
		return "TCP";
#endif

	default:
		return "unknown";
	}
