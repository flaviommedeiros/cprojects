#ifdef USE_NONBLOCKING_CONNECT
if (sock->cotimeout) {
        int errnum, flags;

        /* Get flags and then set O_NONBLOCK. */
        flags = fcntl(fd, F_GETFL);
        if (flags & O_NONBLOCK) {
            /* This socket was created using SOCK_NONBLOCK... flip the
             * bit for restoring flags later. */
            flags &= ~O_NONBLOCK;
        }
        else if (fcntl(fd, F_SETFL, flags | O_NONBLOCK) == -1) {
            set_strerror(sock, errno);
            return NE_SOCK_ERROR;
        }
        
        ret = raw_connect(fd, sa, salen);
        if (ret == -1) {
            errnum = ne_errno;
            if (NE_ISINPROGRESS(errnum)) {
                ret = raw_poll(fd, 1, sock->cotimeout);
                if (ret > 0) { /* poll got data */
                    socklen_t len = sizeof(errnum);
                    
                    /* Check whether there is a pending error for the
                     * socket.  Per Stevens UNPv1Â§15.4, Solaris will
                     * return a pending error via errno by failing the
                     * getsockopt() call. */

                    errnum = 0;
                    if (getsockopt(fd, SOL_SOCKET, SO_ERROR, &errnum, &len))
                        errnum = errno;
                    
                    if (errnum == 0) {
                        ret = 0;
                    } else {
                        set_strerror(sock, errnum);
                        ret = NE_SOCK_ERROR;
                    }
                } else if (ret == 0) { /* poll timed out */
                    set_error(sock, _("Connection timed out"));
                    ret = NE_SOCK_TIMEOUT;
                } else /* poll failed */ {
                    set_strerror(sock, errno);
                    ret = NE_SOCK_ERROR;
                }
            } else /* non-EINPROGRESS error from connect() */ { 
                set_strerror(sock, errnum);
                ret = NE_SOCK_ERROR;
            }
        }
        
        /* Reset to old flags: */
        if (fcntl(fd, F_SETFL, flags) == -1) {
            set_strerror(sock, errno);
            ret = NE_SOCK_ERROR;
        }       
    } else 
#endif /* USE_NONBLOCKING_CONNECT */
    {
        ret = raw_connect(fd, sa, salen);
        
        if (ret < 0) {
            set_strerror(sock, errno);
            ret = NE_SOCK_ERROR;
        }
    }
