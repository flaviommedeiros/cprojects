void Gsm_LPC_Analysis P3((S, s,LARc),
	struct gsm_state *S,
	word 		 * s,		/* 0..159 signals	IN/OUT	*/
        word 		 * LARc)	/* 0..7   LARc's	OUT	*/
{
	longword	L_ACF[9];

#if defined(USE_FLOAT_MUL) && defined(FAST)
	if (S->fast) Fast_Autocorrelation (s,	  L_ACF );
	else
#endif
	Autocorrelation			  (s,	  L_ACF	);
	Reflection_coefficients		  (L_ACF, LARc	);
	Transformation_to_Log_Area_Ratios (LARc);
	Quantization_and_coding		  (LARc);
}
