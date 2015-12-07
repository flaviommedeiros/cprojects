#if defined(BSD42)
if( setsockopt(fd, SOL_SOCKET, options, 0, 0) < 0)
#else /* BSD43 */
       if( setsockopt(fd, SOL_SOCKET, options, (char *)&one, sizeof(one)) < 0)
#endif /* BDS42 */
           sockets_err("setsockopt");
