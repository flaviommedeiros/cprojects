switch (mode) {
        case SCM_ROUND_FLOOR: r = floor(v); break;
        case SCM_ROUND_CEIL:  r = ceil(v); break;
        /* trunc is neither in ANSI nor in POSIX. */
#ifdef HAVE_TRUNC
        case SCM_ROUND_TRUNC: r = trunc(v); break;
#else
        case SCM_ROUND_TRUNC: r = (v < 0.0)? ceil(v) : floor(v); break;
#endif
        case SCM_ROUND_ROUND: r = roundeven(v); break;
        default: Scm_Panic("something screwed up");
        }
