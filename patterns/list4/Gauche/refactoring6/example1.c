if (LONG_MIN <= val
#if SIZEOF_LONG == 4
        && val <= LONG_MAX
#else
        && val <= nextafter((double)LONG_MAX, 0.0)
#endif
        )
        return Scm_MakeBignumFromSI((long)val);
