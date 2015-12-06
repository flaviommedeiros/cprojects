#  ifdef WITH_COMMAND_SOCKET
if (this->type == RAD_LISTEN_COMMAND) {
		this->recv = command_tcp_recv;
		this->send = command_tcp_send;
		command_write_magic(this->fd, sock);
	} else
#  endif
	{

		this->recv = dual_tcp_recv;

#  ifdef WITH_TLS
		if (this->tls) {
			this->recv = dual_tls_recv;
			this->send = dual_tls_send;
		}
#  endif
	}
