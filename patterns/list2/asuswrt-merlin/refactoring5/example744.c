#ifdef ENABLE_CLI_ASKPASS_HELPER
if (want_askpass())
	{
		password = gui_getpass(prompt);
		if (!password) {
			dropbear_exit("No password");
		}
	} else
#endif
	{
		password = getpass_or_cancel(prompt);
	}
