if ((nsent == -1) &&
#if defined(EAGAIN) && EAGAIN != EWOULDBLOCK
                     (socket_errno() != EAGAIN) &&
#endif
                     (socket_errno() != EWOULDBLOCK)) {
                __xmlIOErr(XML_FROM_HTTP, 0, "send failed\n");
                if (total_sent == 0)
                    total_sent = -1;
                break;
            } else {
                /*
                 * No data sent
                 * Since non-blocking sockets are used, wait for
                 * socket to be writable or default timeout prior
                 * to retrying.
                 */
#ifndef HAVE_POLL_H
#ifndef _WINSOCKAPI_
                if (ctxt->fd > FD_SETSIZE)
                    return -1;
#endif

                tv.tv_sec = timeout;
                tv.tv_usec = 0;
                FD_ZERO(&wfd);
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4018)
#endif
                FD_SET(ctxt->fd, &wfd);
#ifdef _MSC_VER
#pragma warning(pop)
#endif
                (void) select(ctxt->fd + 1, NULL, &wfd, NULL, &tv);
#else
                p.fd = ctxt->fd;
                p.events = POLLOUT;
                (void) poll(&p, 1, timeout * 1000);
#endif /* !HAVE_POLL_H */
            }
