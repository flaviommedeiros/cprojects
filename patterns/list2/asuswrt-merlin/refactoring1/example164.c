if (!(inet_pton(AF_INET, source, &source_addr->in.sin_addr) > 0))
	    {
#if defined(SO_BINDTODEVICE)
	      source_addr->in.sin_addr.s_addr = INADDR_ANY;
	      strncpy(interface, source, IF_NAMESIZE - 1);
#else
	      return _("interface binding not supported");
#endif
	    }
#endif
