#ifdef HAVE_KQUEUE
if (errno == EAGAIN || errno == ENOBUFS)
#else
            if (errno == EAGAIN)
#endif
            {
                if (swSocket_wait(task_notify_pipe->getFd(task_notify_pipe, 1), -1, SW_EVENT_WRITE) == 0)
                {
                    continue;
                }
            }
