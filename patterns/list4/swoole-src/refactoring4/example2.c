#ifdef HAVE_KQUEUE
if (ret < 0 && (errno == EAGAIN || errno == ENOBUFS))
#else
            if (ret < 0 && errno == EAGAIN)
#endif
            {
                if (thread->reactor.set(&thread->reactor, pipe_fd, SW_FD_PIPE | SW_EVENT_READ | SW_EVENT_WRITE) < 0)
                {
                    swSysError("reactor->set(%d, PIPE | READ | WRITE) failed.", pipe_fd);
                }
                goto append_pipe_buffer;
            }
