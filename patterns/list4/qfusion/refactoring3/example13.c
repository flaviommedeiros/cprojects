switch( type )
	{
	case SOCKET_LOOPBACK:
		NET_InitAddress( &socketaddress, NA_LOOPBACK );
		if( !NET_OpenSocket( &cls.socket_loopback, SOCKET_LOOPBACK, &socketaddress, false ) )
		{
			Com_Error( ERR_FATAL, "Couldn't open the loopback socket: %s\n", NET_ErrorString() ); // FIXME
			return;
		}
		cls.socket = &cls.socket_loopback;
		cls.reliable = false;
		break;

	case SOCKET_UDP:
		cls.socket = ( address->type == NA_IP6 ?  &cls.socket_udp6 :  &cls.socket_udp );
		cls.reliable = false;
		break;

#ifdef TCP_ALLOW_CONNECT
	case SOCKET_TCP:
		NET_InitAddress( &socketaddress, address->type );
		if( !NET_OpenSocket( &cls.socket_tcp, SOCKET_TCP, &socketaddress, false ) )
		{
			Com_Error( ERR_FATAL, "Couldn't open the TCP socket\n" ); // FIXME
			return;
		}
		NET_SetSocketNoDelay( &cls.socket_tcp, 1 );
		cls.socket = &cls.socket_tcp;
		cls.reliable = true;
		break;
#endif

	default:
		assert( false );
		return;
	}
