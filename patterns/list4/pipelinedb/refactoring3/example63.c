switch (ind_type)
								{
									case ECPGt_short:
									case ECPGt_unsigned_short:
										*((short *) (ind + ind_offset * act_tuple)) = size;
										break;
									case ECPGt_int:
									case ECPGt_unsigned_int:
										*((int *) (ind + ind_offset * act_tuple)) = size;
										break;
									case ECPGt_long:
									case ECPGt_unsigned_long:
										*((long *) (ind + ind_offset * act_tuple)) = size;
										break;
#ifdef HAVE_LONG_LONG_INT
									case ECPGt_long_long:
									case ECPGt_unsigned_long_long:
										*((long long int *) (ind + ind_offset * act_tuple)) = size;
										break;
#endif   /* HAVE_LONG_LONG_INT */
									default:
										break;
								}
