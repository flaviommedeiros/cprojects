if (type != RPC_TYPE_MGN &&
#ifdef WLC_HIGH
	    type != RPC_TYPE_RTN &&
#endif
	     *xaction != rpci->oe_trans) {
#ifdef WLC_HIGH
		if (verbose) {
			RPC_ERR(("Transaction mismatch: expected:0x%x got:0x%x type: %d\n",
				rpci->oe_trans, *xaction, type));
		}
#endif
		return HDR_XACTION_MISMATCH;
	}
