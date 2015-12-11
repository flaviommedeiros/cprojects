socket_t* sockets [] =
	{
		&cls.socket_loopback,
		&cls.socket_udp,
		&cls.socket_udp6,
#ifdef TCP_ALLOW_CONNECT
		&cls.socket_tcp
#endif
	};
