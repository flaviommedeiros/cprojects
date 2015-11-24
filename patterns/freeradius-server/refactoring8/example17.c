int getaddrinfo(char const *hostname, char const *servname, struct addrinfo const *hints, struct addrinfo **res)
{
	struct addrinfo	*cur, *prev = NULL;
	struct hostent	*hp;
	struct hostent	result;
	struct in_addr	in;
	int		i, socktype, proto;
	uint16_t	port = 0;
	int		error;
	char		buffer[2048];

	if (hints && (hints->ai_family != PF_INET) && (hints->ai_family != PF_UNSPEC)) return EAI_FAMILY;

	socktype = (hints && hints->ai_socktype) ? hints->ai_socktype : SOCK_STREAM;
	if (hints && hints->ai_protocol) {
		proto = hints->ai_protocol;
	} else {
		switch (socktype) {
		case SOCK_DGRAM:
			proto = IPPROTO_UDP;
			break;
		case SOCK_STREAM:
			proto = IPPROTO_TCP;
			break;
		default:
			proto = 0;
			break;
		}
	}

	if (servname) {
		if (isdigit((int)*servname)) {
			port = htons(atoi(servname));
		} else {
			struct		servent *se;
			char const	*pe_proto;

			switch (socktype) {
			case SOCK_DGRAM:
				pe_proto = "udp";
				break;

			case SOCK_STREAM:
				pe_proto = "tcp";
				break;

			default:
				pe_proto = NULL;
				break;
			}
			if ((se = getservbyname(servname, pe_proto)) == NULL) return EAI_SERVICE;

			port = se->s_port;
		}
	}

	if (!hostname) {
		if (hints && hints->ai_flags & AI_PASSIVE) {
			*res = malloc_ai(port, htonl(0x00000000), socktype, proto);
		} else {
			*res = malloc_ai(port, htonl(0x7f000001), socktype, proto);
		}
		if (!*res) return EAI_MEMORY;

		return 0;
	}

	/* Numeric IP Address */
	if (inet_aton(hostname, &in)) {
		*res = malloc_ai(port, in.s_addr, socktype, proto);
		if (!*res) return EAI_MEMORY;

		return 0;
	}

	if (hints && hints->ai_flags & AI_NUMERICHOST) return EAI_NONAME;

	/* DNS Lookup */
#ifdef GETHOSTBYNAMERSTYLE
#  if GETHOSTBYNAMERSTYLE == SYSVSTYLE
	hp = gethostbyname_r(hostname, &result, buffer, sizeof(buffer), &error);
#  elif GETHOSTBYNAMERSTYLE == GNUSTYLE
	if (gethostbyname_r(hostname, &result, buffer, sizeof(buffer), &hp, &error) != 0) hp = NULL;
#  else
	hp = gethostbyname_r(hostname, &result, buffer, sizeof(buffer), &error);
#  endif
#else
	hp = gethostbyname_r(hostname, &result, buffer, sizeof(buffer), &error);
#endif

	if (hp && hp->h_name && hp->h_name[0] && hp->h_addr_list[0]) {
		for (i = 0; hp->h_addr_list[i]; i++) {
			if ((cur = malloc_ai(port, ((struct in_addr *)hp->h_addr_list[i])->s_addr,
					     socktype, proto)) == NULL) {
				if (*res) freeaddrinfo(*res);
				return EAI_MEMORY;
			}

			if (prev) {
				prev->ai_next = cur;
			} else {
				*res = cur;
			}
			prev = cur;
		}

		if (hints && hints->ai_flags & AI_CANONNAME && *res) {
			if (((*res)->ai_canonname = strdup(hp->h_name)) == NULL) {
				freeaddrinfo(*res);
				return EAI_MEMORY;
			}
		}
		return 0;
	}
	return EAI_NONAME;
}
