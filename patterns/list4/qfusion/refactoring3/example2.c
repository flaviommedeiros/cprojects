switch( socket->type )
	{
	case SOCKET_LOOPBACK:
		return NET_Loopback_GetPacket( socket, address, message );

	case SOCKET_UDP:
		return NET_UDP_GetPacket( socket, address, message );

#ifdef TCP_SUPPORT
	case SOCKET_TCP:
		return NET_TCP_GetPacket( socket, address, message );
#endif

	default:
		assert( false );
		NET_SetErrorString( "Unknown socket type" );
		return -1;
	}
