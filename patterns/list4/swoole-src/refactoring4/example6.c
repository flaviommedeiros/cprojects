#ifdef HAVE_KQUEUE
if (errno == EAGAIN || errno == ENOBUFS)
#else
            else if (errno == EAGAIN)
#endif
            {
                swSocket_wait(__fd, SW_WORKER_WAIT_TIMEOUT, SW_EVENT_WRITE);
                continue;
            }
            else
            {
                swSysError("write %d bytes failed.", __len);
                return SW_ERR;
            }
