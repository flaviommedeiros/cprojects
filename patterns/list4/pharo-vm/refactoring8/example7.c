static void Weighting_filter P2((e, x),
	register word	* e,		/* signal [-5..0.39.44]	IN  */
	word		* x		/* signal [0..39]	OUT */
)
/*
 *  The coefficients of the weighting filter are stored in a table
 *  (see table 4.4).  The following scaling is used:
 *
 *	H[0..10] = integer( real_H[ 0..10] * 8192 ); 
 */
{
	/* word			wt[ 50 ]; */

	register longword	L_result;
	register int		k /* , i */ ;

	/*  Initialization of a temporary working array wt[0...49]
	 */

	/* for (k =  0; k <=  4; k++) wt[k] = 0;
	 * for (k =  5; k <= 44; k++) wt[k] = *e++;
	 * for (k = 45; k <= 49; k++) wt[k] = 0;
	 *
	 *  (e[-5..-1] and e[40..44] are allocated by the caller,
	 *  are initially zero and are not written anywhere.)
	 */
	e -= 5;

	/*  Compute the signal x[0..39]
	 */ 
	for (k = 0; k <= 39; k++) {

		L_result = 8192 >> 1;

		/* for (i = 0; i <= 10; i++) {
		 *	L_temp   = GSM_L_MULT( wt[k+i], gsm_H[i] );
		 *	L_result = GSM_L_ADD( L_result, L_temp );
		 * }
		 */

#undef	STEP
#define	STEP( i, H )	(e[ k + i ] * (longword)H)

		/*  Every one of these multiplications is done twice --
		 *  but I don't see an elegant way to optimize this. 
		 *  Do you?
		 */

#ifdef	STUPID_COMPILER
		L_result += STEP(	0, 	-134 ) ;
		L_result += STEP(	1, 	-374 )  ;
	               /* + STEP(	2, 	0    )  */
		L_result += STEP(	3, 	2054 ) ;
		L_result += STEP(	4, 	5741 ) ;
		L_result += STEP(	5, 	8192 ) ;
		L_result += STEP(	6, 	5741 ) ;
		L_result += STEP(	7, 	2054 ) ;
	 	       /* + STEP(	8, 	0    )  */
		L_result += STEP(	9, 	-374 ) ;
		L_result += STEP(	10, 	-134 ) ;
#else
		L_result +=
		  STEP(	0, 	-134 ) 
		+ STEP(	1, 	-374 ) 
	     /* + STEP(	2, 	0    )  */
		+ STEP(	3, 	2054 ) 
		+ STEP(	4, 	5741 ) 
		+ STEP(	5, 	8192 ) 
		+ STEP(	6, 	5741 ) 
		+ STEP(	7, 	2054 ) 
	     /* + STEP(	8, 	0    )  */
		+ STEP(	9, 	-374 ) 
		+ STEP(10, 	-134 )
		;
#endif

		/* L_result = GSM_L_ADD( L_result, L_result ); (* scaling(x2) *)
		 * L_result = GSM_L_ADD( L_result, L_result ); (* scaling(x4) *)
		 *
		 * x[k] = SASR( L_result, 16 );
		 */

		/* 2 adds vs. >>16 => 14, minus one shift to compensate for
		 * those we lost when replacing L_MULT by '*'.
		 */

		L_result = SASR( L_result, 13 );
		x[k] =  (  L_result < MIN_WORD ? MIN_WORD
			: (L_result > MAX_WORD ? MAX_WORD : L_result ));
	}
}
