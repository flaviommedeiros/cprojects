#ifdef BCMHOSTVARS
if ((w & 0xffff) == 0)
				sii->pub.boardvendor = VENDOR_BROADCOM;
			else
#endif /* !BCMHOSTVARS */
				sii->pub.boardvendor = w & 0xffff;
