#ifdef HAVE_LOCALE_T
if (mylocale)
			result = strcoll_l(a1p, a2p, mylocale);
		else
#endif
			result = strcoll(a1p, a2p);
