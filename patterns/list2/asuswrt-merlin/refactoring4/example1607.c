#ifdef USE_OBSOLETE_SIGCONTEXT_FLAVOR
if(0 == sigaction(SIGILL, NULL, &sigill_save) && signal(SIGILL, (void (*)(int))sigill_handler_sse_os) != SIG_ERR)
#else
			struct sigaction sigill_sse;
