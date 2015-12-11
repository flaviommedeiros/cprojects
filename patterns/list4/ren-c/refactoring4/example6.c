#ifndef NO_ERRNO
if (!(word0(&rv) & Exp_mask))
#else
        if (word0(&rv) == 0 && word1(&rv) == 0)
#endif
            errno = ERANGE;
