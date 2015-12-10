switch (method) {
#ifdef PROVIDE_ISLOW_TABLES
    case JDCT_ISLOW:
      {
	/* For LL&M IDCT method, multipliers are equal to raw quantization
	 * coefficients, but are stored as ints to ensure access efficiency.
	 */
	ISLOW_MULT_TYPE * ismtbl = (ISLOW_MULT_TYPE *) compptr->dct_table;
	for (i = 0; i < DCTSIZE2; i++) {
	  ismtbl[i] = (ISLOW_MULT_TYPE) qtbl->quantval[i];
	}
      }
      break;
#endif
#ifdef DCT_IFAST_SUPPORTED
    case JDCT_IFAST:
      {
	/* For AA&N IDCT method, multipliers are equal to quantization
	 * coefficients scaled by scalefactor[row]*scalefactor[col], where
	 *   scalefactor[0] = 1
	 *   scalefactor[k] = cos(k*PI/16) * sqrt(2)    for k=1..7
	 * For integer operation, the multiplier table is to be scaled by
	 * IFAST_SCALE_BITS.
	 */
	IFAST_MULT_TYPE * ifmtbl = (IFAST_MULT_TYPE *) compptr->dct_table;
#ifdef ANDROID_ARMV6_IDCT
	/* Precomputed values scaled up by 15 bits. */
	static const unsigned short scales[DCTSIZE2] = {
	  32768, 45451, 42813, 38531, 32768, 25746, 17734,  9041,
	  45451, 63042, 59384, 53444, 45451, 35710, 24598, 12540,
	  42813, 59384, 55938, 50343, 42813, 33638, 23170, 11812,
	  38531, 53444, 50343, 45308, 38531, 30274, 20853, 10631,
	  32768, 45451, 42813, 38531, 32768, 25746, 17734,  9041,
	  25746, 35710, 33638, 30274, 25746, 20228, 13933,  7103,
	  17734, 24598, 23170, 20853, 17734, 13933,  9598,  4893,
	   9041, 12540, 11812, 10631,  9041,  7103,  4893,  2494,
	};
	/* Inverse map of [7, 5, 1, 3, 0, 2, 4, 6]. */
	static const char orders[DCTSIZE] = {4, 2, 5, 3, 6, 1, 7, 0};
	/* Reorder the columns after transposing. */
	for (i = 0; i < DCTSIZE2; ++i) {
	  int j = ((i & 7) << 3) + orders[i >> 3];
	  ifmtbl[j] = (qtbl->quantval[i] * scales[i] + 2) >> 2;
	}
#else /* ANDROID_ARMV6_IDCT */

#define CONST_BITS 14
	static const INT16 aanscales[DCTSIZE2] = {
	  /* precomputed values scaled up by 14 bits */
	  16384, 22725, 21407, 19266, 16384, 12873,  8867,  4520,
	  22725, 31521, 29692, 26722, 22725, 17855, 12299,  6270,
	  21407, 29692, 27969, 25172, 21407, 16819, 11585,  5906,
	  19266, 26722, 25172, 22654, 19266, 15137, 10426,  5315,
	  16384, 22725, 21407, 19266, 16384, 12873,  8867,  4520,
	  12873, 17855, 16819, 15137, 12873, 10114,  6967,  3552,
	   8867, 12299, 11585, 10426,  8867,  6967,  4799,  2446,
	   4520,  6270,  5906,  5315,  4520,  3552,  2446,  1247
	};
	SHIFT_TEMPS

	for (i = 0; i < DCTSIZE2; i++) {
	  ifmtbl[i] = (IFAST_MULT_TYPE)
	    DESCALE(MULTIPLY16V16((INT32) qtbl->quantval[i],
				  (INT32) aanscales[i]),
		    CONST_BITS-IFAST_SCALE_BITS);
	}
#endif /* ANDROID_ARMV6_IDCT */
      }
      break;
#endif
#ifdef DCT_FLOAT_SUPPORTED
    case JDCT_FLOAT:
      {
	/* For float AA&N IDCT method, multipliers are equal to quantization
	 * coefficients scaled by scalefactor[row]*scalefactor[col], where
	 *   scalefactor[0] = 1
	 *   scalefactor[k] = cos(k*PI/16) * sqrt(2)    for k=1..7
	 */
	FLOAT_MULT_TYPE * fmtbl = (FLOAT_MULT_TYPE *) compptr->dct_table;
	int row, col;
	static const double aanscalefactor[DCTSIZE] = {
	  1.0, 1.387039845, 1.306562965, 1.175875602,
	  1.0, 0.785694958, 0.541196100, 0.275899379
	};

	i = 0;
	for (row = 0; row < DCTSIZE; row++) {
	  for (col = 0; col < DCTSIZE; col++) {
	    fmtbl[i] = (FLOAT_MULT_TYPE)
	      ((double) qtbl->quantval[i] *
	       aanscalefactor[row] * aanscalefactor[col]);
	    i++;
	  }
	}
      }
      break;
#endif
    default:
      ERREXIT(cinfo, JERR_NOT_COMPILED);
      break;
    }
