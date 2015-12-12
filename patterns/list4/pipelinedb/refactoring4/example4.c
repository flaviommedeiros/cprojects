#ifdef WIN32
if (err != 0 ||
			getaddrinfo("::1", NULL, &hints, &gai_result) != 0)
			conflines = replace_token(conflines,
							   "host    all             all             ::1",
							 "#host    all             all             ::1");
