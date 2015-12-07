#			if defined(SO_RCVBUFFORCE)
if(setsockopt(*s, SOL_SOCKET, SO_RCVBUFFORCE, &rcvbuf, sizeof(rcvbuf)) < 0)
#			endif
			{
				/* if we fail, try to do it the regular way. Experiments show that at 
				 * least some platforms do not return an error here, but silently set
				 * it to the max permitted value. So we do our error check a bit
				 * differently by querying the size below.
				 */
				setsockopt(*s, SOL_SOCKET, SO_RCVBUF, &rcvbuf, sizeof(rcvbuf));
			}
