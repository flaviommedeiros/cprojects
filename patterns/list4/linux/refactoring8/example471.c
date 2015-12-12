static struct nfsd4_operation nfsd4_ops[] = {
	[OP_ACCESS] = {
		.op_func = (nfsd4op_func)nfsd4_access,
		.op_name = "OP_ACCESS",
	},
	[OP_CLOSE] = {
		.op_func = (nfsd4op_func)nfsd4_close,
		.op_flags = OP_MODIFIES_SOMETHING,
		.op_name = "OP_CLOSE",
		.op_rsize_bop = (nfsd4op_rsize)nfsd4_status_stateid_rsize,
		.op_get_currentstateid = (stateid_getter)nfsd4_get_closestateid,
		.op_set_currentstateid = (stateid_setter)nfsd4_set_closestateid,
	},
	[OP_COMMIT] = {
		.op_func = (nfsd4op_func)nfsd4_commit,
		.op_flags = OP_MODIFIES_SOMETHING,
		.op_name = "OP_COMMIT",
		.op_rsize_bop = (nfsd4op_rsize)nfsd4_commit_rsize,
	},
	[OP_CREATE] = {
		.op_func = (nfsd4op_func)nfsd4_create,
		.op_flags = OP_MODIFIES_SOMETHING | OP_CACHEME | OP_CLEAR_STATEID,
		.op_name = "OP_CREATE",
		.op_rsize_bop = (nfsd4op_rsize)nfsd4_create_rsize,
	},
	[OP_DELEGRETURN] = {
		.op_func = (nfsd4op_func)nfsd4_delegreturn,
		.op_flags = OP_MODIFIES_SOMETHING,
		.op_name = "OP_DELEGRETURN",
		.op_rsize_bop = nfsd4_only_status_rsize,
		.op_get_currentstateid = (stateid_getter)nfsd4_get_delegreturnstateid,
	},
	[OP_GETATTR] = {
		.op_func = (nfsd4op_func)nfsd4_getattr,
		.op_flags = ALLOWED_ON_ABSENT_FS,
		.op_rsize_bop = nfsd4_getattr_rsize,
		.op_name = "OP_GETATTR",
	},
	[OP_GETFH] = {
		.op_func = (nfsd4op_func)nfsd4_getfh,
		.op_name = "OP_GETFH",
	},
	[OP_LINK] = {
		.op_func = (nfsd4op_func)nfsd4_link,
		.op_flags = ALLOWED_ON_ABSENT_FS | OP_MODIFIES_SOMETHING
				| OP_CACHEME,
		.op_name = "OP_LINK",
		.op_rsize_bop = (nfsd4op_rsize)nfsd4_link_rsize,
	},
	[OP_LOCK] = {
		.op_func = (nfsd4op_func)nfsd4_lock,
		.op_flags = OP_MODIFIES_SOMETHING,
		.op_name = "OP_LOCK",
		.op_rsize_bop = (nfsd4op_rsize)nfsd4_lock_rsize,
		.op_set_currentstateid = (stateid_setter)nfsd4_set_lockstateid,
	},
	[OP_LOCKT] = {
		.op_func = (nfsd4op_func)nfsd4_lockt,
		.op_name = "OP_LOCKT",
	},
	[OP_LOCKU] = {
		.op_func = (nfsd4op_func)nfsd4_locku,
		.op_flags = OP_MODIFIES_SOMETHING,
		.op_name = "OP_LOCKU",
		.op_rsize_bop = (nfsd4op_rsize)nfsd4_status_stateid_rsize,
		.op_get_currentstateid = (stateid_getter)nfsd4_get_lockustateid,
	},
	[OP_LOOKUP] = {
		.op_func = (nfsd4op_func)nfsd4_lookup,
		.op_flags = OP_HANDLES_WRONGSEC | OP_CLEAR_STATEID,
		.op_name = "OP_LOOKUP",
	},
	[OP_LOOKUPP] = {
		.op_func = (nfsd4op_func)nfsd4_lookupp,
		.op_flags = OP_HANDLES_WRONGSEC | OP_CLEAR_STATEID,
		.op_name = "OP_LOOKUPP",
	},
	[OP_NVERIFY] = {
		.op_func = (nfsd4op_func)nfsd4_nverify,
		.op_name = "OP_NVERIFY",
	},
	[OP_OPEN] = {
		.op_func = (nfsd4op_func)nfsd4_open,
		.op_flags = OP_HANDLES_WRONGSEC | OP_MODIFIES_SOMETHING,
		.op_name = "OP_OPEN",
		.op_rsize_bop = (nfsd4op_rsize)nfsd4_open_rsize,
		.op_set_currentstateid = (stateid_setter)nfsd4_set_openstateid,
	},
	[OP_OPEN_CONFIRM] = {
		.op_func = (nfsd4op_func)nfsd4_open_confirm,
		.op_flags = OP_MODIFIES_SOMETHING,
		.op_name = "OP_OPEN_CONFIRM",
		.op_rsize_bop = (nfsd4op_rsize)nfsd4_status_stateid_rsize,
	},
	[OP_OPEN_DOWNGRADE] = {
		.op_func = (nfsd4op_func)nfsd4_open_downgrade,
		.op_flags = OP_MODIFIES_SOMETHING,
		.op_name = "OP_OPEN_DOWNGRADE",
		.op_rsize_bop = (nfsd4op_rsize)nfsd4_status_stateid_rsize,
		.op_get_currentstateid = (stateid_getter)nfsd4_get_opendowngradestateid,
		.op_set_currentstateid = (stateid_setter)nfsd4_set_opendowngradestateid,
	},
	[OP_PUTFH] = {
		.op_func = (nfsd4op_func)nfsd4_putfh,
		.op_flags = ALLOWED_WITHOUT_FH | ALLOWED_ON_ABSENT_FS
				| OP_IS_PUTFH_LIKE | OP_CLEAR_STATEID,
		.op_name = "OP_PUTFH",
		.op_rsize_bop = (nfsd4op_rsize)nfsd4_only_status_rsize,
	},
	[OP_PUTPUBFH] = {
		.op_func = (nfsd4op_func)nfsd4_putrootfh,
		.op_flags = ALLOWED_WITHOUT_FH | ALLOWED_ON_ABSENT_FS
				| OP_IS_PUTFH_LIKE | OP_CLEAR_STATEID,
		.op_name = "OP_PUTPUBFH",
		.op_rsize_bop = (nfsd4op_rsize)nfsd4_only_status_rsize,
	},
	[OP_PUTROOTFH] = {
		.op_func = (nfsd4op_func)nfsd4_putrootfh,
		.op_flags = ALLOWED_WITHOUT_FH | ALLOWED_ON_ABSENT_FS
				| OP_IS_PUTFH_LIKE | OP_CLEAR_STATEID,
		.op_name = "OP_PUTROOTFH",
		.op_rsize_bop = (nfsd4op_rsize)nfsd4_only_status_rsize,
	},
	[OP_READ] = {
		.op_func = (nfsd4op_func)nfsd4_read,
		.op_name = "OP_READ",
		.op_rsize_bop = (nfsd4op_rsize)nfsd4_read_rsize,
		.op_get_currentstateid = (stateid_getter)nfsd4_get_readstateid,
	},
	[OP_READDIR] = {
		.op_func = (nfsd4op_func)nfsd4_readdir,
		.op_name = "OP_READDIR",
		.op_rsize_bop = (nfsd4op_rsize)nfsd4_readdir_rsize,
	},
	[OP_READLINK] = {
		.op_func = (nfsd4op_func)nfsd4_readlink,
		.op_name = "OP_READLINK",
	},
	[OP_REMOVE] = {
		.op_func = (nfsd4op_func)nfsd4_remove,
		.op_flags = OP_MODIFIES_SOMETHING | OP_CACHEME,
		.op_name = "OP_REMOVE",
		.op_rsize_bop = (nfsd4op_rsize)nfsd4_remove_rsize,
	},
	[OP_RENAME] = {
		.op_func = (nfsd4op_func)nfsd4_rename,
		.op_flags = OP_MODIFIES_SOMETHING | OP_CACHEME,
		.op_name = "OP_RENAME",
		.op_rsize_bop = (nfsd4op_rsize)nfsd4_rename_rsize,
	},
	[OP_RENEW] = {
		.op_func = (nfsd4op_func)nfsd4_renew,
		.op_flags = ALLOWED_WITHOUT_FH | ALLOWED_ON_ABSENT_FS
				| OP_MODIFIES_SOMETHING,
		.op_name = "OP_RENEW",
		.op_rsize_bop = (nfsd4op_rsize)nfsd4_only_status_rsize,

	},
	[OP_RESTOREFH] = {
		.op_func = (nfsd4op_func)nfsd4_restorefh,
		.op_flags = ALLOWED_WITHOUT_FH | ALLOWED_ON_ABSENT_FS
				| OP_IS_PUTFH_LIKE | OP_MODIFIES_SOMETHING,
		.op_name = "OP_RESTOREFH",
		.op_rsize_bop = (nfsd4op_rsize)nfsd4_only_status_rsize,
	},
	[OP_SAVEFH] = {
		.op_func = (nfsd4op_func)nfsd4_savefh,
		.op_flags = OP_HANDLES_WRONGSEC | OP_MODIFIES_SOMETHING,
		.op_name = "OP_SAVEFH",
		.op_rsize_bop = (nfsd4op_rsize)nfsd4_only_status_rsize,
	},
	[OP_SECINFO] = {
		.op_func = (nfsd4op_func)nfsd4_secinfo,
		.op_flags = OP_HANDLES_WRONGSEC,
		.op_name = "OP_SECINFO",
	},
	[OP_SETATTR] = {
		.op_func = (nfsd4op_func)nfsd4_setattr,
		.op_name = "OP_SETATTR",
		.op_flags = OP_MODIFIES_SOMETHING | OP_CACHEME,
		.op_rsize_bop = (nfsd4op_rsize)nfsd4_setattr_rsize,
		.op_get_currentstateid = (stateid_getter)nfsd4_get_setattrstateid,
	},
	[OP_SETCLIENTID] = {
		.op_func = (nfsd4op_func)nfsd4_setclientid,
		.op_flags = ALLOWED_WITHOUT_FH | ALLOWED_ON_ABSENT_FS
				| OP_MODIFIES_SOMETHING | OP_CACHEME,
		.op_name = "OP_SETCLIENTID",
		.op_rsize_bop = (nfsd4op_rsize)nfsd4_setclientid_rsize,
	},
	[OP_SETCLIENTID_CONFIRM] = {
		.op_func = (nfsd4op_func)nfsd4_setclientid_confirm,
		.op_flags = ALLOWED_WITHOUT_FH | ALLOWED_ON_ABSENT_FS
				| OP_MODIFIES_SOMETHING | OP_CACHEME,
		.op_name = "OP_SETCLIENTID_CONFIRM",
		.op_rsize_bop = (nfsd4op_rsize)nfsd4_only_status_rsize,
	},
	[OP_VERIFY] = {
		.op_func = (nfsd4op_func)nfsd4_verify,
		.op_name = "OP_VERIFY",
	},
	[OP_WRITE] = {
		.op_func = (nfsd4op_func)nfsd4_write,
		.op_flags = OP_MODIFIES_SOMETHING | OP_CACHEME,
		.op_name = "OP_WRITE",
		.op_rsize_bop = (nfsd4op_rsize)nfsd4_write_rsize,
		.op_get_currentstateid = (stateid_getter)nfsd4_get_writestateid,
	},
	[OP_RELEASE_LOCKOWNER] = {
		.op_func = (nfsd4op_func)nfsd4_release_lockowner,
		.op_flags = ALLOWED_WITHOUT_FH | ALLOWED_ON_ABSENT_FS
				| OP_MODIFIES_SOMETHING,
		.op_name = "OP_RELEASE_LOCKOWNER",
		.op_rsize_bop = (nfsd4op_rsize)nfsd4_only_status_rsize,
	},

	/* NFSv4.1 operations */
	[OP_EXCHANGE_ID] = {
		.op_func = (nfsd4op_func)nfsd4_exchange_id,
		.op_flags = ALLOWED_WITHOUT_FH | ALLOWED_AS_FIRST_OP
				| OP_MODIFIES_SOMETHING,
		.op_name = "OP_EXCHANGE_ID",
		.op_rsize_bop = (nfsd4op_rsize)nfsd4_exchange_id_rsize,
	},
	[OP_BACKCHANNEL_CTL] = {
		.op_func = (nfsd4op_func)nfsd4_backchannel_ctl,
		.op_flags = ALLOWED_WITHOUT_FH | OP_MODIFIES_SOMETHING,
		.op_name = "OP_BACKCHANNEL_CTL",
		.op_rsize_bop = (nfsd4op_rsize)nfsd4_only_status_rsize,
	},
	[OP_BIND_CONN_TO_SESSION] = {
		.op_func = (nfsd4op_func)nfsd4_bind_conn_to_session,
		.op_flags = ALLOWED_WITHOUT_FH | ALLOWED_AS_FIRST_OP
				| OP_MODIFIES_SOMETHING,
		.op_name = "OP_BIND_CONN_TO_SESSION",
		.op_rsize_bop = (nfsd4op_rsize)nfsd4_bind_conn_to_session_rsize,
	},
	[OP_CREATE_SESSION] = {
		.op_func = (nfsd4op_func)nfsd4_create_session,
		.op_flags = ALLOWED_WITHOUT_FH | ALLOWED_AS_FIRST_OP
				| OP_MODIFIES_SOMETHING,
		.op_name = "OP_CREATE_SESSION",
		.op_rsize_bop = (nfsd4op_rsize)nfsd4_create_session_rsize,
	},
	[OP_DESTROY_SESSION] = {
		.op_func = (nfsd4op_func)nfsd4_destroy_session,
		.op_flags = ALLOWED_WITHOUT_FH | ALLOWED_AS_FIRST_OP
				| OP_MODIFIES_SOMETHING,
		.op_name = "OP_DESTROY_SESSION",
		.op_rsize_bop = (nfsd4op_rsize)nfsd4_only_status_rsize,
	},
	[OP_SEQUENCE] = {
		.op_func = (nfsd4op_func)nfsd4_sequence,
		.op_flags = ALLOWED_WITHOUT_FH | ALLOWED_AS_FIRST_OP,
		.op_name = "OP_SEQUENCE",
		.op_rsize_bop = (nfsd4op_rsize)nfsd4_sequence_rsize,
	},
	[OP_DESTROY_CLIENTID] = {
		.op_func = (nfsd4op_func)nfsd4_destroy_clientid,
		.op_flags = ALLOWED_WITHOUT_FH | ALLOWED_AS_FIRST_OP
				| OP_MODIFIES_SOMETHING,
		.op_name = "OP_DESTROY_CLIENTID",
		.op_rsize_bop = (nfsd4op_rsize)nfsd4_only_status_rsize,
	},
	[OP_RECLAIM_COMPLETE] = {
		.op_func = (nfsd4op_func)nfsd4_reclaim_complete,
		.op_flags = ALLOWED_WITHOUT_FH | OP_MODIFIES_SOMETHING,
		.op_name = "OP_RECLAIM_COMPLETE",
		.op_rsize_bop = (nfsd4op_rsize)nfsd4_only_status_rsize,
	},
	[OP_SECINFO_NO_NAME] = {
		.op_func = (nfsd4op_func)nfsd4_secinfo_no_name,
		.op_flags = OP_HANDLES_WRONGSEC,
		.op_name = "OP_SECINFO_NO_NAME",
	},
	[OP_TEST_STATEID] = {
		.op_func = (nfsd4op_func)nfsd4_test_stateid,
		.op_flags = ALLOWED_WITHOUT_FH,
		.op_name = "OP_TEST_STATEID",
	},
	[OP_FREE_STATEID] = {
		.op_func = (nfsd4op_func)nfsd4_free_stateid,
		.op_flags = ALLOWED_WITHOUT_FH | OP_MODIFIES_SOMETHING,
		.op_name = "OP_FREE_STATEID",
		.op_get_currentstateid = (stateid_getter)nfsd4_get_freestateid,
		.op_rsize_bop = (nfsd4op_rsize)nfsd4_only_status_rsize,
	},
#ifdef CONFIG_NFSD_PNFS
	[OP_GETDEVICEINFO] = {
		.op_func = (nfsd4op_func)nfsd4_getdeviceinfo,
		.op_flags = ALLOWED_WITHOUT_FH,
		.op_name = "OP_GETDEVICEINFO",
	},
	[OP_LAYOUTGET] = {
		.op_func = (nfsd4op_func)nfsd4_layoutget,
		.op_flags = OP_MODIFIES_SOMETHING,
		.op_name = "OP_LAYOUTGET",
		.op_rsize_bop = (nfsd4op_rsize)nfsd4_layoutget_rsize,
	},
	[OP_LAYOUTCOMMIT] = {
		.op_func = (nfsd4op_func)nfsd4_layoutcommit,
		.op_flags = OP_MODIFIES_SOMETHING,
		.op_name = "OP_LAYOUTCOMMIT",
		.op_rsize_bop = (nfsd4op_rsize)nfsd4_layoutcommit_rsize,
	},
	[OP_LAYOUTRETURN] = {
		.op_func = (nfsd4op_func)nfsd4_layoutreturn,
		.op_flags = OP_MODIFIES_SOMETHING,
		.op_name = "OP_LAYOUTRETURN",
		.op_rsize_bop = (nfsd4op_rsize)nfsd4_layoutreturn_rsize,
	},
#endif /* CONFIG_NFSD_PNFS */

	/* NFSv4.2 operations */
	[OP_ALLOCATE] = {
		.op_func = (nfsd4op_func)nfsd4_allocate,
		.op_flags = OP_MODIFIES_SOMETHING | OP_CACHEME,
		.op_name = "OP_ALLOCATE",
		.op_rsize_bop = (nfsd4op_rsize)nfsd4_only_status_rsize,
	},
	[OP_DEALLOCATE] = {
		.op_func = (nfsd4op_func)nfsd4_deallocate,
		.op_flags = OP_MODIFIES_SOMETHING | OP_CACHEME,
		.op_name = "OP_DEALLOCATE",
		.op_rsize_bop = (nfsd4op_rsize)nfsd4_only_status_rsize,
	},
	[OP_SEEK] = {
		.op_func = (nfsd4op_func)nfsd4_seek,
		.op_name = "OP_SEEK",
	},
};
