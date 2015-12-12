if ((value != HUGE_VAL)
#ifdef HAVE_ERRNO
                || (errno != ERANGE)
#endif /* HAVE_ERRNO */
                ) {
                ASSERT(value == value);
                while (*endptr && IsSpace(*endptr)) endptr++;
                if (!*endptr) {
                    if (d) *d = value;
                    return True;
                }
            }
