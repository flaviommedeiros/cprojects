switch (server->rcv.state) {
			case 0:
				if (server->rcv.buf.magic != htonl(NCP_TCP_RCVD_MAGIC)) {
					printk(KERN_ERR "ncpfs: tcp: Unexpected reply type %08X\n", ntohl(server->rcv.buf.magic));
					__ncptcp_abort(server);
					return -EIO;
				}
				datalen = ntohl(server->rcv.buf.len) & 0x0FFFFFFF;
				if (datalen < 10) {
					printk(KERN_ERR "ncpfs: tcp: Unexpected reply len %d\n", datalen);
					__ncptcp_abort(server);
					return -EIO;
				}
#ifdef CONFIG_NCPFS_PACKET_SIGNING				
				if (server->sign_active) {
					if (datalen < 18) {
						printk(KERN_ERR "ncpfs: tcp: Unexpected reply len %d\n", datalen);
						__ncptcp_abort(server);
						return -EIO;
					}
					server->rcv.buf.len = datalen - 8;
					server->rcv.ptr = (unsigned char*)&server->rcv.buf.p1;
					server->rcv.len = 8;
					server->rcv.state = 4;
					break;
				}
#endif				
				type = ntohs(server->rcv.buf.type);
#ifdef CONFIG_NCPFS_PACKET_SIGNING				
cont:;				
#endif
				if (type != NCP_REPLY) {
					if (datalen - 8 <= sizeof(server->unexpected_packet.data)) {
						*(__u16*)(server->unexpected_packet.data) = htons(type);
						server->unexpected_packet.len = datalen - 8;

						server->rcv.state = 5;
						server->rcv.ptr = server->unexpected_packet.data + 2;
						server->rcv.len = datalen - 10;
						break;
					}					
					DPRINTK("ncpfs: tcp: Unexpected NCP type %02X\n", type);
skipdata2:;
					server->rcv.state = 2;
skipdata:;
					server->rcv.ptr = NULL;
					server->rcv.len = datalen - 10;
					break;
				}
				req = server->rcv.creq;
				if (!req) {
					DPRINTK(KERN_ERR "ncpfs: Reply without appropriate request\n");
					goto skipdata2;
				}
				if (datalen > req->datalen + 8) {
					printk(KERN_ERR "ncpfs: tcp: Unexpected reply len %d (expected at most %Zd)\n", datalen, req->datalen + 8);
					server->rcv.state = 3;
					goto skipdata;
				}
				req->datalen = datalen - 8;
				((struct ncp_reply_header*)server->rxbuf)->type = NCP_REPLY;
				server->rcv.ptr = server->rxbuf + 2;
				server->rcv.len = datalen - 10;
				server->rcv.state = 1;
				break;
#ifdef CONFIG_NCPFS_PACKET_SIGNING				
			case 4:
				datalen = server->rcv.buf.len;
				type = ntohs(server->rcv.buf.type2);
				goto cont;
#endif
			case 1:
				req = server->rcv.creq;
				if (req->tx_type != NCP_ALLOC_SLOT_REQUEST) {
					if (((struct ncp_reply_header*)server->rxbuf)->sequence != server->sequence) {
						printk(KERN_ERR "ncpfs: tcp: Bad sequence number\n");
						__ncp_abort_request(server, req, -EIO);
						return -EIO;
					}
					if ((((struct ncp_reply_header*)server->rxbuf)->conn_low | (((struct ncp_reply_header*)server->rxbuf)->conn_high << 8)) != server->connection) {
						printk(KERN_ERR "ncpfs: tcp: Connection number mismatch\n");
						__ncp_abort_request(server, req, -EIO);
						return -EIO;
					}
				}
#ifdef CONFIG_NCPFS_PACKET_SIGNING				
				if (server->sign_active && req->tx_type != NCP_DEALLOC_SLOT_REQUEST) {
					if (sign_verify_reply(server, server->rxbuf + 6, req->datalen - 6, cpu_to_be32(req->datalen + 16), &server->rcv.buf.type)) {
						printk(KERN_ERR "ncpfs: tcp: Signature violation\n");
						__ncp_abort_request(server, req, -EIO);
						return -EIO;
					}
				}
#endif				
				ncp_finish_request(server, req, req->datalen);
			nextreq:;
				__ncp_next_request(server);
			case 2:
			next:;
				server->rcv.ptr = (unsigned char*)&server->rcv.buf;
				server->rcv.len = 10;
				server->rcv.state = 0;
				break;
			case 3:
				ncp_finish_request(server, server->rcv.creq, -EIO);
				goto nextreq;
			case 5:
				info_server(server, 0, server->unexpected_packet.data, server->unexpected_packet.len);
				goto next;
		}
