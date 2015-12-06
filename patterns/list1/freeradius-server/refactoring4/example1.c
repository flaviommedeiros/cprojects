#ifdef HAVE_SIGACTION
if (sigaction(signo, &act, &oact) < 0)
		return SIG_ERR;
