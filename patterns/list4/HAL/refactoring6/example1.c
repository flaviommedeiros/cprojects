if ((number != LONG_MAX && number != LONG_MIN)
#ifdef HAVE_ERRNO
                || (errno != ERANGE)
#endif /* HAVE_ERRNO */
                ) {
                while (*endptr && IsSpace(*endptr)) endptr++;
                if (!*endptr) {
                    if (n) *n = number;
                    return True;
                }
            }
