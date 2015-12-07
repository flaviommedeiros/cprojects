if (us->ppa == 0 || msgdsize(mp) > us->ppa->mtu + PPP_HDRLEN
#ifndef NO_DLPI
	    || (us->flags & US_CONTROL) == 0
#endif /* NO_DLPI */
	    ) {
	    DPRINT1("pppuwput: junk data len=%d\n", msgdsize(mp));
	    freemsg(mp);
	    break;
	}
