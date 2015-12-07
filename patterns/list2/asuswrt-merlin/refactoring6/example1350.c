if (hints != NULL
	&& hints->ai_family != PF_UNSPEC
	&& hints->ai_family != PF_INET
#ifdef HAVE_IPV6
	&& hints->ai_family != PF_INET6
#endif
	)
	return EAI_FAMILY;
