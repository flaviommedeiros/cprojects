while ((res =
#ifdef SUPPORT_RMT
		rmtread_with_restart(arfd, scbuf, sizeof(scbuf))
#else
		read_with_restart(arfd, scbuf, sizeof(scbuf))
#endif /* SUPPORT_RMT */
	       ) > 0)
		;
