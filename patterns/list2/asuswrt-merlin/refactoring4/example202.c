#ifdef SO_NOSIGPIPE
if (setsockopt(sd, SOL_SOCKET, SO_NOSIGPIPE, &optval, sizeof(optval)) < 0)
		LogMsg("%3d: WARNING: setsockopt - SO_NOSIGPIPE %d (%s)", sd, dnssd_errno, dnssd_strerror(dnssd_errno));
