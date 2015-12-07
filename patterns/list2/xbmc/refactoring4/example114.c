#if HAVE_PLIBC_FD
if (ioctlsocket (plibc_fd_get_handle (socket_fd), FIONBIO, &sk_flags) ==
          SOCKET_ERROR)
#else
      if (ioctlsocket (socket_fd, FIONBIO, &sk_flags) == SOCKET_ERROR)
#endif // PLIBC_FD
        goto thread_failed;
