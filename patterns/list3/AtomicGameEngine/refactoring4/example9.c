#ifdef USE_WINSOCK
if(WSAEWOULDBLOCK == err)
#else
    if((EWOULDBLOCK == err) || (EAGAIN == err) || (EINTR == err))
#endif
      return CURLE_AGAIN;
    else
      return CURLE_RECV_ERROR;
