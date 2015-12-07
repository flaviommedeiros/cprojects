#ifdef AF_INET6
if (ia->ai_family == AF_INET6) {
	struct sockaddr_in6 *in6 = SACAST(in6, ia->ai_addr);
        return memcpy(buf, in6->sin6_addr.s6_addr, sizeof in6->sin6_addr.s6_addr);
    } else
#endif /* AF_INET6 */
    {
	struct sockaddr_in *in = SACAST(in, ia->ai_addr);
        return memcpy(buf, &in->sin_addr.s_addr, sizeof in->sin_addr.s_addr);
    }
