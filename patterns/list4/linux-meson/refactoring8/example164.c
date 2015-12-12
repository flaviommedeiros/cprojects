static inline void dump_cmsg(enum debuglevel level, const char *tag, _cmsg *p)
{
#ifdef CONFIG_GIGASET_DEBUG
	/* dump at most 20 messages in 20 secs */
	static DEFINE_RATELIMIT_STATE(msg_dump_ratelimit, 20 * HZ, 20);
	_cdebbuf *cdb;

	if (!(gigaset_debuglevel & level))
		return;
	if (!___ratelimit(&msg_dump_ratelimit, tag))
		return;

	cdb = capi_cmsg2str(p);
	if (cdb) {
		gig_dbg(level, "%s: [%d] %s", tag, p->ApplId, cdb->buf);
		cdebbuf_free(cdb);
	} else {
		gig_dbg(level, "%s: [%d] %s", tag, p->ApplId,
			capi_cmd2str(p->Command, p->Subcommand));
	}
#endif
}
