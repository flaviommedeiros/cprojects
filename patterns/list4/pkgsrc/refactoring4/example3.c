#ifdef WITH_SSL
if ((urltype == HTTP_URL_T && portnum != HTTP_PORT) ||
			    (urltype == HTTPS_URL_T && portnum != HTTPS_PORT))
#else
			if (portnum != HTTP_PORT)
#endif
				fetch_printf(fin, ":%u", portnum);
