#ifndef SW_WORKER_RECV_AGAIN
if (task.info.type == SW_EVENT_PACKAGE_START)
#endif
        {
            //no data
            if (ret < 0 && errno == EAGAIN)
            {
                return SW_OK;
            }
            else if (ret > 0)
            {
                goto read_from_pipe;
            }
        }
