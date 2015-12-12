if ((si == 1) &&
	    (l2 != ISDN_PROTO_L2_MODEM)
#ifdef CONFIG_ISDN_TTY_FAX
	    && (l2 != ISDN_PROTO_L2_FAX)
#endif
		) {
		l2 = ISDN_PROTO_L2_TRANS;
		usg = ISDN_USAGE_VOICE;
	}
