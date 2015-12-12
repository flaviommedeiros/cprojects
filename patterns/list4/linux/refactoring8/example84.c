static inline void dump_rawmsg(enum debuglevel level, const char *tag,
			       unsigned char *data)
{
#ifdef CONFIG_GIGASET_DEBUG
	char *dbgline;
	int i, l;

	if (!(gigaset_debuglevel & level))
		return;

	l = CAPIMSG_LEN(data);
	if (l < 12) {
		gig_dbg(level, "%s: ??? LEN=%04d", tag, l);
		return;
	}
	gig_dbg(level, "%s: 0x%02x:0x%02x: ID=%03d #0x%04x LEN=%04d NCCI=0x%x",
		tag, CAPIMSG_COMMAND(data), CAPIMSG_SUBCOMMAND(data),
		CAPIMSG_APPID(data), CAPIMSG_MSGID(data), l,
		CAPIMSG_CONTROL(data));
	l -= 12;
	if (l <= 0)
		return;
	if (l > 64)
		l = 64; /* arbitrary limit */
	dbgline = kmalloc(3 * l, GFP_ATOMIC);
	if (!dbgline)
		return;
	for (i = 0; i < l; i++) {
		dbgline[3 * i] = hex_asc_hi(data[12 + i]);
		dbgline[3 * i + 1] = hex_asc_lo(data[12 + i]);
		dbgline[3 * i + 2] = ' ';
	}
	dbgline[3 * l - 1] = '\0';
	gig_dbg(level, "  %s", dbgline);
	kfree(dbgline);
	if (CAPIMSG_COMMAND(data) == CAPI_DATA_B3 &&
	    (CAPIMSG_SUBCOMMAND(data) == CAPI_REQ ||
	     CAPIMSG_SUBCOMMAND(data) == CAPI_IND)) {
		l = CAPIMSG_DATALEN(data);
		gig_dbg(level, "   DataLength=%d", l);
		if (l <= 0 || !(gigaset_debuglevel & DEBUG_LLDATA))
			return;
		if (l > 64)
			l = 64; /* arbitrary limit */
		dbgline = kmalloc(3 * l, GFP_ATOMIC);
		if (!dbgline)
			return;
		data += CAPIMSG_LEN(data);
		for (i = 0; i < l; i++) {
			dbgline[3 * i] = hex_asc_hi(data[i]);
			dbgline[3 * i + 1] = hex_asc_lo(data[i]);
			dbgline[3 * i + 2] = ' ';
		}
		dbgline[3 * l - 1] = '\0';
		gig_dbg(level, "  %s", dbgline);
		kfree(dbgline);
	}
#endif
}
