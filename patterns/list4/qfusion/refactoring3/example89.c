switch (errno) {
# ifdef EINTR
            case EINTR:
# endif
# ifdef EAGAIN
            case EAGAIN:
# endif
# ifdef EINPROGRESS
            case EINPROGRESS:
# endif
# ifdef EALREADY
            case EALREADY:
# endif
                /* No error, try again */
                break;
# ifdef EISCONN
            case EISCONN:
                success = 1;
                break;
# endif
            default:
                goto err;       /* failure */
            }
