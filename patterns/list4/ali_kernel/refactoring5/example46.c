#ifdef BCM_CNIC
if (cid == BNX2X_FCOE_ETH_CID)
		return &bnx2x_fcoe(bp, q_obj);
	else
#endif
		return &bnx2x_fp(bp, CID_TO_FP(cid), q_obj);
