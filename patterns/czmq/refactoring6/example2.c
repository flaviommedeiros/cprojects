if (errno == EAGAIN
    ||  errno == ENETDOWN
    ||  errno == EHOSTUNREACH
    ||  errno == ENETUNREACH
    ||  errno == EINTR
    ||  errno == EPIPE
    ||  errno == ECONNRESET
#if defined (ENOPROTOOPT)
    ||  errno == ENOPROTOOPT
#endif
#if defined (EHOSTDOWN)
    ||  errno == EHOSTDOWN
#endif
#if defined (EOPNOTSUPP)
    ||  errno == EOPNOTSUPP
#endif
#if defined (EWOULDBLOCK)
    ||  errno == EWOULDBLOCK
#endif
#if defined (EPROTO)
    ||  errno == EPROTO
#endif
#if defined (ENONET)
    ||  errno == ENONET
#endif
    )
        return;             //  Ignore error and try again
    else {
        zclock_log ("E: (UDP) error '%s' on %s", strerror (errno), reason);
        assert (false);
    }
