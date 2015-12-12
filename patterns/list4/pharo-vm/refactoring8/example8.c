void Gsm_Short_Term_Analysis_Filter P3((S,LARc,s),

	struct gsm_state * S,

	word	* LARc,		/* coded log area ratio [0..7]  IN	*/
	word	* s		/* signal [0..159]		IN/OUT	*/
)
{
	word		* LARpp_j	= S->LARpp[ S->j      ];
	word		* LARpp_j_1	= S->LARpp[ S->j ^= 1 ];

	word		LARp[8];

#undef	FILTER
#if 	defined(FAST) && defined(USE_FLOAT_MUL)
# 	define	FILTER 	(* (S->fast			\
			   ? Fast_Short_term_analysis_filtering	\
		    	   : Short_term_analysis_filtering	))

#else
# 	define	FILTER	Short_term_analysis_filtering
#endif

	Decoding_of_the_coded_Log_Area_Ratios( LARc, LARpp_j );

	Coefficients_0_12(  LARpp_j_1, LARpp_j, LARp );
	LARp_to_rp( LARp );
	FILTER( S, LARp, 13, s);

	Coefficients_13_26( LARpp_j_1, LARpp_j, LARp);
	LARp_to_rp( LARp );
	FILTER( S, LARp, 14, s + 13);

	Coefficients_27_39( LARpp_j_1, LARpp_j, LARp);
	LARp_to_rp( LARp );
	FILTER( S, LARp, 13, s + 27);

	Coefficients_40_159( LARpp_j, LARp);
	LARp_to_rp( LARp );
	FILTER( S, LARp, 120, s + 40);
}
