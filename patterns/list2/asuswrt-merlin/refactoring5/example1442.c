# ifdef ENOTTY
if (errno == ENOTTY)
            is_a_tty = 0;
        else
# endif
# ifdef EINVAL
            /*
             * Ariel Glenn ariel@columbia.edu reports that solaris can return
             * EINVAL instead.  This should be ok
             */
        if (errno == EINVAL)
            is_a_tty = 0;
        else
# endif
            return 0;
