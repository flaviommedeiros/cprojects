static void Autocorrelation P2((s, L_ACF),
	word     * s,		/* [0..159]	IN/OUT  */
 	longword * L_ACF)	/* [0..8]	OUT     */
/*
 *  The goal is to compute the array L_ACF[k].  The signal s[i] must
 *  be scaled in order to avoid an overflow situation.
 */
{
	register int	k, i;

	word		temp, smax, scalauto;

#ifdef	USE_FLOAT_MUL
	float		float_s[160];
#endif

	/*  Dynamic scaling of the array  s[0..159]
	 */

	/*  Search for the maximum.
	 */
	smax = 0;
	for (k = 0; k <= 159; k++) {
		temp = GSM_ABS( s[k] );
		if (temp > smax) smax = temp;
	}

	/*  Computation of the scaling factor.
	 */
	if (smax == 0) scalauto = 0;
	else {
		assert(smax > 0);
		scalauto = 4 - gsm_norm( (longword)smax << 16 );/* sub(4,..) */
	}

	/*  Scaling of the array s[0...159]
	 */

	if (scalauto > 0) {

# ifdef USE_FLOAT_MUL
#   define SCALE(n)	\
	case n: for (k = 0; k <= 159; k++) \
			float_s[k] = (float)	\
				(s[k] = GSM_MULT_R(s[k], 16384 >> (n-1)));\
		break;
# else 
#   define SCALE(n)	\
	case n: for (k = 0; k <= 159; k++) \
			s[k] = GSM_MULT_R( s[k], 16384 >> (n-1) );\
		break;
# endif /* USE_FLOAT_MUL */

		switch (scalauto) {
		SCALE(1)
		SCALE(2)
		SCALE(3)
		SCALE(4)
		}
# undef	SCALE
	}
# ifdef	USE_FLOAT_MUL
	else for (k = 0; k <= 159; k++) float_s[k] = (float) s[k];
# endif

	/*  Compute the L_ACF[..].
	 */
	{
# ifdef	USE_FLOAT_MUL
		register float * sp = float_s;
		register float   sl = *sp;

#		define STEP(k)	 L_ACF[k] += (longword)(sl * sp[ -(k) ]);
# else
		word  * sp = s;
		word    sl = *sp;

#		define STEP(k)	 L_ACF[k] += ((longword)sl * sp[ -(k) ]);
# endif

#	define NEXTI	 sl = *++sp


	for (k = 9; k--; L_ACF[k] = 0) ;

	STEP (0);
	NEXTI;
	STEP(0); STEP(1);
	NEXTI;
	STEP(0); STEP(1); STEP(2);
	NEXTI;
	STEP(0); STEP(1); STEP(2); STEP(3);
	NEXTI;
	STEP(0); STEP(1); STEP(2); STEP(3); STEP(4);
	NEXTI;
	STEP(0); STEP(1); STEP(2); STEP(3); STEP(4); STEP(5);
	NEXTI;
	STEP(0); STEP(1); STEP(2); STEP(3); STEP(4); STEP(5); STEP(6);
	NEXTI;
	STEP(0); STEP(1); STEP(2); STEP(3); STEP(4); STEP(5); STEP(6); STEP(7);

	for (i = 8; i <= 159; i++) {

		NEXTI;

		STEP(0);
		STEP(1); STEP(2); STEP(3); STEP(4);
		STEP(5); STEP(6); STEP(7); STEP(8);
	}

	for (k = 9; k--; L_ACF[k] <<= 1) ; 

	}
	/*   Rescaling of the array s[0..159]
	 */
	if (scalauto > 0) {
		assert(scalauto <= 4); 
		for (k = 160; k--; *s++ <<= scalauto) ;
	}
}
