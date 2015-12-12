if (endptr != token + length || errno == ERANGE
#ifdef HAVE_LONG_INT_64
		/* if long > 32 bits, check for overflow of int4 */
			|| val != (long) ((int32) val)
#endif
			)
			return T_Float;
