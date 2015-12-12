#ifdef SUPPORT_RMT
while ((res = rmtread_with_restart(arfd,
						   scbuf, sizeof(scbuf))) > 0)
#else
		while ((res = read_with_restart(arfd,
						scbuf, sizeof(scbuf))) > 0)
#endif /* SUPPORT_RMT */
			padsz += res;
