switch( sockets[i]->type )
		{
		case SOCKET_UDP:
#ifdef TCP_SUPPORT
		case SOCKET_TCP:
#endif
			assert( sockets[i]->handle > 0 );
			fdmax = max( (int)sockets[i]->handle, fdmax );
			FD_SET( sockets[i]->handle, &fdsetr ); // network socket
			if( p_fdsetw )
				FD_SET( sockets[i]->handle, p_fdsetw );
			if( p_fdsete )
				FD_SET( sockets[i]->handle, p_fdsete );
			break;
		case SOCKET_LOOPBACK:
		default:
			continue;
		}
