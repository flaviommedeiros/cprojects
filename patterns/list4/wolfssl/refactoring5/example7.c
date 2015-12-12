#ifdef BN_FAST_S_MP_MUL_DIGS_C
if ((digs < MP_WARRAY) &&
        MIN(a->used, b->used) <=
        (1 << ((CHAR_BIT * sizeof (mp_word)) - (2 * DIGIT_BIT)))) {
      res = fast_s_mp_mul_digs (a, b, c, digs);
    } else
#endif
#ifdef BN_S_MP_MUL_DIGS_C
      res = s_mp_mul (a, b, c);
