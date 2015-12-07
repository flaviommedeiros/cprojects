#ifdef HISAX_UINTERFACE
if (test_bit(FLG_L1_UINT, &st->l1.Flags))
		FsmChangeState(fi, ST_L1_TRANS);
	else
#endif
		FsmChangeState(fi, ST_L1_F7);
