#ifdef LTP_CUT
if (S->ltp_cut)
			Cut_Calculation_of_the_LTP_parameters(S, d, dp, bc, Nc);
		else
#endif
			Calculation_of_the_LTP_parameters(d, dp, bc, Nc);
