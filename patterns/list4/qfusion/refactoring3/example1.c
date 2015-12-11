switch( type )
	{
	case SOCKET_UDP:
		handle = socket( protocol, SOCK_DGRAM, IPPROTO_UDP );
		if( handle == INVALID_SOCKET )
		{
			NET_SetErrorStringFromLastError( "socket" );
			return INVALID_SOCKET;
		}
		break;

#ifdef TCP_SUPPORT
	case SOCKET_TCP:
		handle = socket( protocol, SOCK_STREAM, IPPROTO_TCP );
		if( handle == INVALID_SOCKET )
		{
			NET_SetErrorStringFromLastError( "socket" );
			return INVALID_SOCKET;
		}
		else
		{
			struct linger ling;

			ling.l_onoff = 1;
			ling.l_linger = 5;		// 0 for abortive disconnect

			if( setsockopt( handle, SOL_SOCKET, SO_LINGER, (char *)&ling, sizeof( ling ) ) < 0 )
			{
				NET_SetErrorStringFromLastError( "socket" );
				return INVALID_SOCKET;
			}
		}
		break;
#endif

	default:
		NET_SetErrorString( "Unknown socket type" );
		return INVALID_SOCKET;
	}
