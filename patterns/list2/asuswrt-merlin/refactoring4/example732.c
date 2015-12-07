#ifdef TOMATO
if(signal(SIGPIPE, SIG_IGN) == SIG_ERR)
#else	/* TOMATO */
	sa.sa_handler = SIG_IGN;
