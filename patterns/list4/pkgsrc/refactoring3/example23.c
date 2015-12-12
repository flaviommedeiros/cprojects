switch (data_addr.su_family) {
			case AF_INET:
				error = sscanf(pasv,
"%u,%u,%u,%u,%u,%u,%u,%u,%u",
					&af, &hal,
					&addr[0], &addr[1], &addr[2], &addr[3],
					&pal, &port[0], &port[1]);
				if (error != 9) {
					fputs(
"Passive mode address scan failure. Shouldn't happen!\n", ttyout);
					error = 1;
					goto bad;
				}
				if (af != 4 || hal != 4 || pal != 2) {
					fputs(
"Passive mode AF mismatch. Shouldn't happen!\n", ttyout);
					error = 1;
					goto bad;
				}

				error = 0;
				memset(&data_addr, 0, sizeof(data_addr));
				data_addr.su_family = AF_INET;
				data_addr.su_len = sizeof(struct sockaddr_in);
				data_addr.si_su.su_sin.sin_addr.s_addr =
				    htonl(pack4(addr, 0));
				data_addr.su_port = htons(pack2(port, 0));
				break;
#ifdef INET6
			case AF_INET6:
				error = sscanf(pasv,
"%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u",
					&af, &hal,
					&addr[0], &addr[1], &addr[2], &addr[3],
					&addr[4], &addr[5], &addr[6], &addr[7],
					&addr[8], &addr[9], &addr[10],
					&addr[11], &addr[12], &addr[13],
					&addr[14], &addr[15],
					&pal, &port[0], &port[1]);
				if (error != 21) {
					fputs(
"Passive mode address scan failure. Shouldn't happen!\n", ttyout);
					error = 1;
					goto bad;
				}
				if (af != 6 || hal != 16 || pal != 2) {
					fputs(
"Passive mode AF mismatch. Shouldn't happen!\n", ttyout);
					error = 1;
					goto bad;
				}

				error = 0;
				memset(&data_addr, 0, sizeof(data_addr));
				data_addr.su_family = AF_INET6;
				data_addr.su_len = sizeof(struct sockaddr_in6);
			    {
				size_t i;
				for (i = 0; i < sizeof(struct in6_addr); i++) {
					data_addr.si_su.su_sin6.sin6_addr.s6_addr[i] =
					    UC(addr[i]);
				}
			    }
				data_addr.su_port = htons(pack2(port, 0));
				break;
#endif
			default:
				error = 1;
			}
