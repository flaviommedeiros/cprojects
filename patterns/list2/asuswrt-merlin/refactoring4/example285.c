#if !defined (HAVE_BSD_SIGNALS) && !defined (HAVE_POSIX_SIGNALS)
if (sig == SIGINT || sig == SIGALRM)
#  else
  if (sig == SIGINT)
#  endif
    rl_set_sighandler (sig, SIG_IGN, &dummy_cxt);
