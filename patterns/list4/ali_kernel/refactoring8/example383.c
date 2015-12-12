static struct rpc_procinfo	nlm4_procedures[] = {
    PROC(TEST,		testargs,	testres),
    PROC(LOCK,		lockargs,	res),
    PROC(CANCEL,	cancargs,	res),
    PROC(UNLOCK,	unlockargs,	res),
    PROC(GRANTED,	testargs,	res),
    PROC(TEST_MSG,	testargs,	norep),
    PROC(LOCK_MSG,	lockargs,	norep),
    PROC(CANCEL_MSG,	cancargs,	norep),
    PROC(UNLOCK_MSG,	unlockargs,	norep),
    PROC(GRANTED_MSG,	testargs,	norep),
    PROC(TEST_RES,	testres,	norep),
    PROC(LOCK_RES,	res,		norep),
    PROC(CANCEL_RES,	res,		norep),
    PROC(UNLOCK_RES,	res,		norep),
    PROC(GRANTED_RES,	res,		norep),
#ifdef NLMCLNT_SUPPORT_SHARES
    PROC(SHARE,		shareargs,	shareres),
    PROC(UNSHARE,	shareargs,	shareres),
    PROC(NM_LOCK,	lockargs,	res),
    PROC(FREE_ALL,	notify,		void),
#endif
};
