if (week_1stday_l == 19971201
#if SIZEOF_LONG_INT > 4
           || week_1stday_l >> 32 == 19971201
#endif
           )
            week_1stday = 1; /* Mon */
        else
        {
            first_weekday = 1;
            return first_weekday; /* we go for a monday default */
        }
