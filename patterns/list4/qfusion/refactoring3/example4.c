switch( socket->type )
	{
	case SOCKET_LOOPBACK:
		return NET_Loopback_SendPacket( socket, data, length, address );

	case SOCKET_UDP:
		return NET_UDP_SendPacket( socket, data, length, address );

#ifdef TCP_SUPPORT
	case SOCKET_TCP:
		return NET_TCP_SendPacket( socket, data, length );
#endif

	default:
		assert( false );
		NET_SetErrorString( "Unknown socket type" );
		return false;
	}
