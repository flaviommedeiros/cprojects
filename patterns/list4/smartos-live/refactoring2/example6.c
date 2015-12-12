#if defined(XP_WIN)
if (!(JSDOUBLE_IS_FINITE(d) && JSDOUBLE_IS_INFINITE(d2)))
#endif
            d = fmod(d, d2);
