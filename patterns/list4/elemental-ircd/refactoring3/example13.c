switch (error) {
#ifdef WSAEINPROGRESS
    case WSAEINPROGRESS:
#endif
#if defined WSAEWOULDBLOCK
    case WSAEWOULDBLOCK:
#endif
#if defined(WSAEAGAIN) && (WSAEWOULDBLOCK != WSAEAGAIN)
    case WSAEAGAIN:
#endif
#ifdef WSAEINTR
    case WSAEINTR:
#endif
#ifdef WSAERESTART
    case WSAERESTART:
#endif
#ifdef WSAENOBUFS
    case WSAENOBUFS:
#endif
        return 1;
    default:
        break;
    }
