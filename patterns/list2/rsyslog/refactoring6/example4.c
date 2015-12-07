if( (bind(sock, r->ai_addr, r->ai_addrlen) < 0)
#ifndef IPV6_V6ONLY
		     && (errno != EADDRINUSE)
#endif
	           ) {
			/* TODO: check if *we* bound the socket - else we *have* an error! */
			char errStr[1024];
			rs_strerror_r(errno, errStr, sizeof(errStr));
                        dbgprintf("error %d while binding tcp socket: %s\n", errno, errStr);
                	close(sock);
			sock = -1;
                        continue;
                }
