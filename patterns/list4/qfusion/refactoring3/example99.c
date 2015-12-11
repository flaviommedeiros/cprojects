switch (errno) {
# ifdef EINTR
                case EINTR:
# endif
# ifdef EAGAIN
                case EAGAIN:
# endif
                    /* No error, try again */
                    break;
                default:
                    ret = -1;
                    goto err;   /* failure */
                }
