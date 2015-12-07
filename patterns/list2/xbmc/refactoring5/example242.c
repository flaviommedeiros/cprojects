#ifdef FAITH
if (translate && gai_afd->a_af == AF_INET) {
			struct in6_addr *in6;

			GET_AI(cur->ai_next, &gai_afdl[N_INET6], ap, port);
			in6 = &((struct sockaddr_in6 *)cur->ai_next->ai_addr)->sin6_addr;
			memcpy(&in6->s6_addr32[0], &faith_prefix,
			    sizeof(struct in6_addr) - sizeof(struct in_addr));
			memcpy(&in6->s6_addr32[3], ap, sizeof(struct in_addr));
		} else
#endif /* FAITH */
		GET_AI(cur->ai_next, gai_afd, ap, port);
