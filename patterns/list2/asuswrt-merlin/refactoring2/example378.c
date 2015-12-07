#ifdef HAVE_INET_NTOP
if(inet_ntop(AF_INET6, addr->address.data, buf, sizeof(buf)) == NULL)
#endif
	{
	    /* XXX this is pretty ugly, but better than abort() */
	    int i;
	    unsigned char *p = addr->address.data;
	    buf[0] = '\0';
	    for(i = 0; i < addr->address.length; i++) {
		snprintf(buf2, sizeof(buf2), "%02x", p[i]);
		if(i > 0 && (i & 1) == 0)
		    strlcat(buf, ":", sizeof(buf));
		strlcat(buf, buf2, sizeof(buf));
	    }
	}
