switch (error) {
#ifdef EINPROGRESS
    case EINPROGRESS:
#endif
#if defined EWOULDBLOCK
    case EWOULDBLOCK:
#endif
#if defined(EAGAIN) && (EWOULDBLOCK != EAGAIN)
    case EAGAIN:
#endif
#ifdef EINTR
    case EINTR:
#endif
#ifdef ERESTART
    case ERESTART:
#endif
#ifdef ENOBUFS
    case ENOBUFS:
#endif
        return 1;
    default:
        break;
    }
