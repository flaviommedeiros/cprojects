switch( type )
	{
	case SOCKET_LOOPBACK:
		return NET_Loopback_OpenSocket( socket, address, server );

#ifdef TCP_SUPPORT
	case SOCKET_TCP:
#endif
	case SOCKET_UDP:
		return NET_IP_OpenSocket( socket, address, type, server );

	default:
		assert( false );
		NET_SetErrorString( "Unknown socket type" );
		return false;
	}
