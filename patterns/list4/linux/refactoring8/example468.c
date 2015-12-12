static struct rpc_procinfo nfs4_cb_procedures[] = {
	PROC(CB_NULL,	NULL,		cb_null,	cb_null),
	PROC(CB_RECALL,	COMPOUND,	cb_recall,	cb_recall),
#ifdef CONFIG_NFSD_PNFS
	PROC(CB_LAYOUT,	COMPOUND,	cb_layout,	cb_layout),
#endif
};
