#ifdef HAVE_LINUX_IF_PACKET_H
if (raw_mode) {
		if (fr_dhcp_send_raw_packet(sockfd, &ll, request) < 0) {
			ERROR("Failed sending (fr_dhcp_send_raw_packet): %s", fr_syserror(errno));
			return -1;
		}
		if (!reply_expected) return 0;

		*reply = fr_dhcp_recv_raw_loop(sockfd, &ll, request);
		if (!*reply) {
			ERROR("Error receiving reply (fr_dhcp_recv_raw_loop)");
			return -1;
		}
	} else
#endif
	{
		if (fr_dhcp_send_socket(request) < 0) {
			ERROR("Failed sending: %s", fr_syserror(errno));
			return -1;
		}
		if (!reply_expected) return 0;

		*reply = fr_dhcp_recv_socket(sockfd);
		if (!*reply) {
			if (errno == EAGAIN) {
				fr_strerror(); /* clear error */
				ERROR("Timed out waiting for reply");
			} else {
				ERROR("Error receiving reply");
			}
			return -1;
		}
	}
