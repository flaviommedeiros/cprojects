switch( socket->type )
	{
	case SOCKET_LOOPBACK:
		NET_Loopback_CloseSocket( socket );
		break;

	case SOCKET_UDP:
		NET_UDP_CloseSocket( socket );
		break;

#ifdef TCP_SUPPORT
	case SOCKET_TCP:
		NET_TCP_CloseSocket( socket );
		break;
#endif

	default:
		assert( false );
		NET_SetErrorString( "Unknown socket type" );
		break;
	}
