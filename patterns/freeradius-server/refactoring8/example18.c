int getnameinfo(struct sockaddr const  *sa, socklen_t salen, char *host, size_t hostlen, char *serv, size_t servlen,
		unsigned int flags)
{
	const struct	sockaddr_in *sin = (struct sockaddr_in const *)sa;
	struct hostent	*hp;
	struct hostent	result;
	char		tmpserv[16];
	char		buffer[2048];
	int		error;

	if (serv) {
		snprintf(tmpserv, sizeof(tmpserv), "%d", ntohs(sin->sin_port));
		if (strlen(tmpserv) > servlen) return EAI_MEMORY;

		strcpy(serv, tmpserv);

		if (host) {
			if (flags & NI_NUMERICHOST) {
				/*  No Reverse DNS lookup */
				if (flags & NI_NAMEREQD) return EAI_NONAME;
				if (strlen(inet_ntoa(sin->sin_addr)) >= hostlen) return EAI_MEMORY;

				strcpy(host, inet_ntoa(sin->sin_addr));
				return 0;
			} else {
	/*  Reverse DNS lookup required */
#ifdef GETHOSTBYADDRRSTYLE
#  if GETHOSTBYADDRRSTYLE == SYSVSTYLE
			hp = gethostbyaddr_r((char const *)&sin->sin_addr,
					     salen, AF_INET, &result, buffer, sizeof(buffer), &error);
#  elif GETHOSTBYADDRRSTYLE == GNUSTYLE
			if (gethostbyaddr_r((char const *)&sin->sin_addr, salen, AF_INET,
					    &result, buffer, sizeof(buffer), &hp, &error) != 0) {
				hp = NULL;
		 	}
#  else
			hp = gethostbyaddr_r((char const *)&sin->sin_addr, salen, AF_INET,
					     &result, buffer, sizeof(buffer), &error);
#  endif
#else
			hp = gethostbyaddr_r((char const *)&sin->sin_addr, salen, AF_INET,
					     &result, buffer, sizeof(buffer), &error);
#endif
			if (hp) {
				if (strlen(hp->h_name) >= hostlen) return EAI_MEMORY;

				strcpy(host, hp->h_name);
				return 0;
			}

			if (flags & NI_NAMEREQD) return EAI_NONAME;
			if (strlen(inet_ntoa(sin->sin_addr)) >= hostlen) return EAI_MEMORY;

			strcpy(host, inet_ntoa(sin->sin_addr));
			return 0;
		}
	}
	return 0;
}
