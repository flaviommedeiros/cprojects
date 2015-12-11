struct option long_options[] = {
		{"use-file",          required_argument, 0, 'f'},
		{"vrrp",              no_argument,       0, 'P'},
		{"check",             no_argument,       0, 'C'},
		{"log-console",       no_argument,       0, 'l'},
		{"log-detail",        no_argument,       0, 'D'},
		{"log-facility",      required_argument, 0, 'S'},
		{"release-vips",      no_argument,       0, 'X'},
		{"dont-release-vrrp", no_argument,       0, 'V'},
		{"dont-release-ipvs", no_argument,       0, 'I'},
		{"dont-respawn",      no_argument,       0, 'R'},
		{"dont-fork",         no_argument,       0, 'n'},
		{"dump-conf",         no_argument,       0, 'd'},
		{"pid",               required_argument, 0, 'p'},
		{"vrrp_pid",          required_argument, 0, 'r'},
		{"checkers_pid",      required_argument, 0, 'c'},
 #ifdef _WITH_SNMP_
		{"snmp",              no_argument,       0, 'x'},
		{"snmp-agent-socket", required_argument, 0, 'A'},
 #endif
		{"version",           no_argument,       0, 'v'},
		{"help",              no_argument,       0, 'h'},
		{0, 0, 0, 0}
	};
