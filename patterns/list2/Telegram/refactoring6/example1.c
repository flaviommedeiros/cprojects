if (
#ifdef EWOULDBLOCK
    err == EWOULDBLOCK ||
#endif
#ifdef WSAEWOULDBLOCK
    err == WSAEWOULDBLOCK ||
#endif
#ifdef ENOTCONN
    err == ENOTCONN ||
#endif
#ifdef EINTR
    err == EINTR ||
#endif
#ifdef EAGAIN
    err == EAGAIN ||
#endif
#ifdef EPROTO
    err == EPROTO ||
#endif
#ifdef EINPROGRESS
    err == EINPROGRESS ||
#endif
#ifdef EALREADY
    err == EALREADY ||
#endif
    0) {
    return 1;
  }
