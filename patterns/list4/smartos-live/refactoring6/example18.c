if (d < 0.0
#if defined(XP_WIN) || defined(XP_OS2)
            && !((word0(d) & Exp_mask) == Exp_mask && ((word0(d) & Frac_mask) || word1(d))) /* Visual C++ doesn't know how to compare against NaN */
#endif
           ) {
            *p++ = '-';
            d = -d;
        }
