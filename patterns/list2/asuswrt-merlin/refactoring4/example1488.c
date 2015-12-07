#ifndef HAVE_POLL_H
if (FD_ISSET(s, &wfd)
#ifdef _WINSOCKAPI_
        || FD_ISSET(s, &xfd)
#endif
        )
#else /* !HAVE_POLL_H */
    if (p.revents == POLLOUT)
#endif /* !HAVE_POLL_H */
    {
        XML_SOCKLEN_T len;

        len = sizeof(status);
#ifdef SO_ERROR
        if (getsockopt(s, SOL_SOCKET, SO_ERROR, (char *) &status, &len) <
            0) {
            /* Solaris error code */
            __xmlIOErr(XML_FROM_HTTP, 0, "getsockopt failed\n");
            return (-1);
        }
#endif
        if (status) {
            __xmlIOErr(XML_FROM_HTTP, 0,
                       "Error connecting to remote host");
            closesocket(s);
            errno = status;
            return (-1);
        }
    } else {
        /* pbm */
        __xmlIOErr(XML_FROM_HTTP, 0, "select failed\n");
        closesocket(s);
        return (-1);
    }
