#ifdef HAVE_UNIX_SOCKETS
if (addr && addr->ss_family == AF_UNIX)
		rc = getnameinfo_unix((const struct sockaddr_un *) addr, salen,
							  node, nodelen,
							  service, servicelen,
							  flags);
	else
#endif
		rc = getnameinfo((const struct sockaddr *) addr, salen,
						 node, nodelen,
						 service, servicelen,
						 flags);
