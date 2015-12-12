return
#ifdef __alpha__
	    /* poll bit 4 (UF) of Control Register C */
	    funkyTOY ? (hclock_read(12) & 0x10) :
#endif
	    /* poll bit 7 (UIP) of Control Register A */
	    (hclock_read(10) & 0x80);
