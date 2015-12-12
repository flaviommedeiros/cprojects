#ifdef LBL_ALIGN
if ((long)bufp & 3) {
			sbp = &sbhdr;
			memcpy(sbp, bufp, sizeof(*sbp));
		} else
#endif
			sbp = (struct sb_hdr *)bufp;
