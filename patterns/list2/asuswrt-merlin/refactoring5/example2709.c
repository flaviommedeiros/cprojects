#ifdef BN_MP_EXPTMOD_FAST_C
if (mp_isodd (P) == 1 || dr !=  0) {
    return mp_exptmod_fast (G, X, P, Y, dr);
  } else {
#endif
#ifdef BN_S_MP_EXPTMOD_C
    /* otherwise use the generic Barrett reduction technique */
    return s_mp_exptmod (G, X, P, Y, 0);
#else
#error mp_exptmod could fail
    /* no exptmod for evens */
    return MP_VAL;
#endif
#ifdef BN_MP_EXPTMOD_FAST_C
  }
