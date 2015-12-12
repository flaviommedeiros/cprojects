if (artyp == ISPIPE
#ifdef SUPPORT_TAPE
	    || artyp == ISTAPE
#endif /* SUPPORT_TAPE */
#ifdef SUPPORT_RMT
	    || artyp == ISRMT
#endif /* SUPPORT_RMT */
	    )
		return 0;
