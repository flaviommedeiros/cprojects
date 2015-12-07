#ifdef AF_INET6
if (ia->ai_family == AF_INET6) {
	struct sockaddr_in6 *in6 = SACAST(in6, ia->ai_addr);
	ret = inet_ntop(AF_INET6, &in6->sin6_addr, buf, bufsiz);
    } else
#endif
    if (ia->ai_family == AF_INET) {
	struct sockaddr_in *in = SACAST(in, ia->ai_addr);
	ret = inet_ntop(AF_INET, &in->sin_addr, buf, bufsiz);
    } else
	ret = NULL;
