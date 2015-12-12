if ((number != INT64_MAX && number != INT64_MIN)
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
