#ifdef LBL_ALIGN
if ((long)bp & 3) {
			sp = &stamp;
			memcpy((char *)sp, (char *)bp, sizeof(*sp));
		} else
#endif
			sp = (struct enstamp *)bp;
