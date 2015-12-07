#if defined(SO_NP_EXTENSIONS)
if (setsockopt(skt, SOL_SOCKET, SO_NP_EXTENSIONS, &sonpx, optlen) < 0)
		my_perror("WARNING: could not set sockopt - SO_NP_EXTENSIONS");
