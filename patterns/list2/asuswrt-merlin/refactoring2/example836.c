#ifdef RTCONFIG_TR069
if(nvram_invmatch("wans_mode", "lb"))
#endif
	{
		char *getip[] = {"getrealip.sh", NULL};
		pid_t pid;

		//_eval(getip, ">>/tmp/log.txt", 0, &pid);
		_eval(getip, ">>/dev/null", 0, &pid);
	}
