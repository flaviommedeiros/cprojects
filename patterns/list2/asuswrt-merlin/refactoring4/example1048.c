#ifdef LINUX_2_6_36
if (!(entry = netconf_generate_entry(NULL, NULL, 0, "DROP", &unused, sizeof(unused))))
		return ENOMEM;
