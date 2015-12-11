switch( socket->type )
	{
	case SOCKET_LOOPBACK:
		break;
	case SOCKET_UDP:
		break;
#ifdef TCP_SUPPORT
	case SOCKET_TCP:
		return NET_TCP_SetNoDelay( socket, nodelay );
#endif
	default:
		assert( false );
		NET_SetErrorString( "Unknown socket type" );
		return -1;
	}
