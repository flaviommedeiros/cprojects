void Gsm_Short_Term_Synthesis_Filter P4((S, LARcr, wt, s),
	struct gsm_state * S,

	word	* LARcr,	/* received log area ratios [0..7] IN  */
	word	* wt,		/* received d [0..159]		   IN  */

	word	* s		/* signal   s [0..159]		  OUT  */
)
{
	word		* LARpp_j	= S->LARpp[ S->j     ];
	word		* LARpp_j_1	= S->LARpp[ S->j ^=1 ];

	word		LARp[8];

#undef	FILTER
#if 	defined(FAST) && defined(USE_FLOAT_MUL)

# 	define	FILTER 	(* (S->fast			\
			   ? Fast_Short_term_synthesis_filtering	\
		    	   : Short_term_synthesis_filtering	))
#else
#	define	FILTER	Short_term_synthesis_filtering
#endif

	Decoding_of_the_coded_Log_Area_Ratios( LARcr, LARpp_j );

	Coefficients_0_12( LARpp_j_1, LARpp_j, LARp );
	LARp_to_rp( LARp );
	FILTER( S, LARp, 13, wt, s );

	Coefficients_13_26( LARpp_j_1, LARpp_j, LARp);
	LARp_to_rp( LARp );
	FILTER( S, LARp, 14, wt + 13, s + 13 );

	Coefficients_27_39( LARpp_j_1, LARpp_j, LARp);
	LARp_to_rp( LARp );
	FILTER( S, LARp, 13, wt + 27, s + 27 );

	Coefficients_40_159( LARpp_j, LARp );
	LARp_to_rp( LARp );
	FILTER(S, LARp, 120, wt + 40, s + 40);
}
