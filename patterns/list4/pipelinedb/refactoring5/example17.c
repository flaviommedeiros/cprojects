#ifdef HAVE_LOCALE_T
if (mylocale)
				result = wcscoll_l((LPWSTR) a1p, (LPWSTR) a2p, mylocale);
			else
#endif
				result = wcscoll((LPWSTR) a1p, (LPWSTR) a2p);
