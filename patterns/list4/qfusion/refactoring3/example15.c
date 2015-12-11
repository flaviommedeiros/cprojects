switch( type )
	{
	case SOCKET_UDP:
		NET_InitAddress( &socketaddress, address->type );
		if( !NET_OpenSocket( &upstream->socket_real, SOCKET_UDP, &socketaddress, false ) )
		{
			Com_Printf( "Error: Couldn't open UDP socket: %s\n", NET_ErrorString() );
			return;
		}
		upstream->socket = &upstream->socket_real;
		upstream->reliable = false;
		upstream->individual_socket = true;
		break;

#ifdef TCP_ALLOW_TVCONNECT
	case SOCKET_TCP:
		NET_InitAddress( &socketaddress, address->type );
		if( !NET_OpenSocket( &upstream->socket_real, SOCKET_TCP, &socketaddress, false ) )
		{
			Com_Printf( "Error: Couldn't open TCP socket: %s\n", NET_ErrorString() );
			return;
		}
		NET_SetSocketNoDelay( &upstream->socket_real, 1 );
		upstream->socket = &upstream->socket_real;
		upstream->reliable = true;
		upstream->individual_socket = true;
		break;
#endif

	case SOCKET_LOOPBACK:
	default:
		assert( false );
	}
