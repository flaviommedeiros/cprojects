if (
#if SIZEOF_LONG >= 8
            mant0 == 0
#else  /*SIZEOF_LONG < 8*/
            mant0 == 0 && mant1 == 0
#endif /*SIZEOF_LONG < 8*/
            ) {
            return sign0? 0xfc00 : 0x7c00;
        } else {
            return 0x7fff;
        }
