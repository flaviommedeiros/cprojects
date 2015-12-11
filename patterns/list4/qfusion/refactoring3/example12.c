switch( sockets[i]->type ) {
			case SOCKET_UDP:
#ifdef TCP_SUPPORT
			case SOCKET_TCP:
#endif
				if ( (exception_cb) && (FD_ISSET(sockets[i]->handle, p_fdsete )) ) {
					exception_cb(sockets[i], privatep ? privatep[i] : NULL);
				}
				if ( (read_cb) && (FD_ISSET(sockets[i]->handle, &fdsetr )) ) {
					read_cb(sockets[i], privatep ? privatep[i] : NULL);
				}
				if ( (write_cb) && (FD_ISSET(sockets[i]->handle, p_fdsetw )) ) {
					write_cb(sockets[i], privatep ? privatep[i] : NULL);
				}
				break;
			case SOCKET_LOOPBACK:
			default:
				continue;
			}
