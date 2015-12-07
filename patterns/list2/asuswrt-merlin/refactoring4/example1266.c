#ifdef LINUX_2_6_36
if (!(entry = netconf_generate_entry("state", &state, sizeof(state), "LOG", &log, sizeof(log))))
		return ENOMEM;
