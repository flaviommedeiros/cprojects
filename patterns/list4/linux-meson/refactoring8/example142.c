static struct shutdown_handler handlers[] = {
		{ "poweroff",	do_poweroff },
		{ "halt",	do_poweroff },
		{ "reboot",	do_reboot   },
#ifdef CONFIG_HIBERNATE_CALLBACKS
		{ "suspend",	do_suspend  },
#endif
		{NULL, NULL},
	};
