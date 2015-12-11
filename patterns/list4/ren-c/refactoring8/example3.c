static CONST double tinytens[] = { 1e-16, 1e-32, 1e-64, 1e-128,
#ifdef Avoid_Underflow
        9007199254740992.*9007199254740992.e-256
        /* = 2^106 * 1e-256 */
#else
        1e-256
#endif
        };
