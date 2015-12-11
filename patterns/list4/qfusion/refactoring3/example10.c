switch( sockets[i]->type )
		{
		case SOCKET_UDP:
#ifdef TCP_SUPPORT
		case SOCKET_TCP:
#endif
			assert( sockets[i]->handle > 0 );
			FD_SET( (unsigned)sockets[i]->handle, &fdset ); // network socket
			break;

		default:
			Com_Printf( "Warning: Invalid socket type on Sys_NET_Sleep\n" );
			return;
		}
