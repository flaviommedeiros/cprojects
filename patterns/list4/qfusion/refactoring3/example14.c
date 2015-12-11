switch( socket->type )
	{
#ifdef TCP_ALLOW_TVCONNECT
	case SOCKET_TCP:
		client->reliable = true;
		client->individual_socket = true;
		client->socket = *socket;
		break;
#endif

	case SOCKET_UDP:
	case SOCKET_LOOPBACK:
		client->reliable = false;
		client->individual_socket = false;
		client->socket.open = false;
		break;

	default:
		assert( false );
	}
