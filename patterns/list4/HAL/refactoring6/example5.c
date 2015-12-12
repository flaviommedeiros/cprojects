if ((number != UINT64_MAX)
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
