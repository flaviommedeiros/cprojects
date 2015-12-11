switch( socket->type )
	{
	case SOCKET_LOOPBACK:
	case SOCKET_UDP:
		NET_SetErrorString( "Operation not supported by the socket type" );
		return -1;

#ifdef TCP_SUPPORT
	case SOCKET_TCP:
		return NET_TCP_Send( socket, data, length );
#endif

	default:
		assert( false );
		NET_SetErrorString( "Unknown socket type" );
		return -1;
	}
