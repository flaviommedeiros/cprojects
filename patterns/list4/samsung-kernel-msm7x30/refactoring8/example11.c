struct list_head audit_filter_list[AUDIT_NR_FILTERS] = {
	LIST_HEAD_INIT(audit_filter_list[0]),
	LIST_HEAD_INIT(audit_filter_list[1]),
	LIST_HEAD_INIT(audit_filter_list[2]),
	LIST_HEAD_INIT(audit_filter_list[3]),
	LIST_HEAD_INIT(audit_filter_list[4]),
	LIST_HEAD_INIT(audit_filter_list[5]),
#if AUDIT_NR_FILTERS != 6
#error Fix audit_filter_list initialiser
#endif
};
