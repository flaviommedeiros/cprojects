if (
#if SIZEOF_LONG >= 8
            mant0 == 0
#else  /*SIZEOF_LONG < 8*/
            mant0 == 0 && mant1 == 0
#endif /*SIZEOF_LONG < 8*/
            ) {
            return SCM_TRUE;  /* infinity */
        } else {
            return SCM_FALSE; /* NaN */
        }
