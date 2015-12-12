switch (vio->type) {
  case VIO_TYPE_TCPIP:
    info->protocol= MYSQL_VIO_TCP;
    info->socket= vio_fd(vio);
    return;
  case VIO_TYPE_SOCKET:
    info->protocol= MYSQL_VIO_SOCKET;
    info->socket= vio_fd(vio);
    return;
  case VIO_TYPE_SSL:
    {
      struct sockaddr addr;
      socklen_t addrlen= sizeof(addr);
      if (getsockname(vio_fd(vio), &addr, &addrlen))
        return;
      info->protocol= addr.sa_family == AF_UNIX ?
        MYSQL_VIO_SOCKET : MYSQL_VIO_TCP;
      info->socket= vio_fd(vio);
      return;
    }
#ifdef _WIN32
  case VIO_TYPE_NAMEDPIPE:
    info->protocol= MYSQL_VIO_PIPE;
    info->handle= vio->hPipe;
    return;
#ifdef HAVE_SMEM
  case VIO_TYPE_SHARED_MEMORY:
    info->protocol= MYSQL_VIO_MEMORY;
    info->handle= vio->handle_file_map; /* or what ? */
    return;
#endif
#endif
  default: DBUG_ASSERT(0);
  }
