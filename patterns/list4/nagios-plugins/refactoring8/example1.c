static struct option longopts[] = {
		{"help", no_argument, 0, 'h'},
		{"version", no_argument, 0, 'V'},
		{"timeout", required_argument, 0, 't'},
		{"hostname", required_argument, 0, 'H'},
		{"uri", required_argument, 0, 'U'},
		{"base", required_argument, 0, 'b'},
		{"attr", required_argument, 0, 'a'},
		{"bind", required_argument, 0, 'D'},
		{"pass", required_argument, 0, 'P'},
#ifdef HAVE_LDAP_SET_OPTION
		{"ver2", no_argument, 0, '2'},
		{"ver3", no_argument, 0, '3'},
#endif
		{"starttls", no_argument, 0, 'T'},
		{"ssl", no_argument, 0, 'S'},
		{"use-ipv4", no_argument, 0, '4'},
		{"use-ipv6", no_argument, 0, '6'},
		{"port", required_argument, 0, 'p'},
		{"warn", required_argument, 0, 'w'},
		{"crit", required_argument, 0, 'c'},
		{"verbose", no_argument, 0, 'v'},
		{0, 0, 0, 0}
	};
