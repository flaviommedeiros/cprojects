#ifdef HISAX_UINTERFACE
if (!test_bit(FLG_L1_UINT, &st->l1.Flags))
#endif
		if (st->l1.l1m.state != ST_L1_F6) {
			FsmChangeState(fi, ST_L1_F3);
			st->l1.l1hw(st, HW_ENABLE | REQUEST, NULL);
		}
