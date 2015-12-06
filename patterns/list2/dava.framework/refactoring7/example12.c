return errno == EAGAIN
      || errno == EINPROGRESS
#ifdef EWOULDBLOCK
      || errno == EWOULDBLOCK;
