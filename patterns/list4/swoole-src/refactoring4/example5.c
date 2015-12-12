#ifndef NO_EPOLLRDHUP
if ((events[i].events & (EPOLLRDHUP | EPOLLERR | EPOLLHUP)) && event.socket->fd && !event.socket->removed)
#else
            if ((events[i].events & (EPOLLERR | EPOLLHUP)) && !event.socket->removed)
#endif
            {
                handle = swReactor_getHandle(reactor, SW_EVENT_ERROR, event.type);
                ret = handle(reactor, &event);
                if (ret < 0)
                {
                    swSysError("EPOLLERR handle failed. fd=%d.", event.fd);
                }
            }
