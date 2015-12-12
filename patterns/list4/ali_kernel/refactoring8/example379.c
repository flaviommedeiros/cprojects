static void flush_warnings(struct dquot *const *dquots, char *warntype)
{
	struct dquot *dq;
	int i;

	for (i = 0; i < MAXQUOTAS; i++) {
		dq = dquots[i];
		if (dq && warntype[i] != QUOTA_NL_NOWARN &&
		    !warning_issued(dq, warntype[i])) {
#ifdef CONFIG_PRINT_QUOTA_WARNING
			print_warning(dq, warntype[i]);
#endif
			quota_send_warning(dq->dq_type, dq->dq_id,
					   dq->dq_sb->s_dev, warntype[i]);
		}
	}
}
