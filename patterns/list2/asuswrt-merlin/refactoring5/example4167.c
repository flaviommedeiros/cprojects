#ifdef BN_FAST_MP_MONTGOMERY_REDUCE_C
if (((P->used * 2 + 1) < MP_WARRAY) &&
          P->used < (1 << ((CHAR_BIT * sizeof (mp_word)) - (2 * DIGIT_BIT)))) {
        redux = fast_mp_montgomery_reduce;
     } else 
#endif
     {
#ifdef BN_MP_MONTGOMERY_REDUCE_C
        /* use slower baseline Montgomery method */
        redux = mp_montgomery_reduce;
#else
        err = MP_VAL;
        goto LBL_M;
#endif
     }
