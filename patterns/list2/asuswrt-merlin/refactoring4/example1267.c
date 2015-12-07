#ifdef LINUX_2_6_36
if (!(entry = netconf_generate_entry(NULL, NULL, 0, "ACCEPT", &unused, sizeof(unused))))
		return ENOMEM;
