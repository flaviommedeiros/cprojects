#ifdef SW_REACTOR_RECV_AGAIN
while (1)
#endif
    {
        n = read(ev->fd, &resp, sizeof(resp));
        if (n > 0)
        {
            memcpy(&_send.info, &resp.info, sizeof(resp.info));
            if (_send.info.from_fd == SW_RESPONSE_SMALL)
            {
                _send.data = resp.data;
                _send.length = resp.info.len;
                swReactorThread_send(&_send);
            }
            else
            {
                memcpy(&pkg_resp, resp.data, sizeof(pkg_resp));
                worker = swServer_get_worker(SwooleG.serv, pkg_resp.worker_id);

                _send.data = worker->send_shm;
                _send.length = pkg_resp.length;

#if 0
                struct
                {
                    uint32_t worker;
                    uint32_t index;
                    uint32_t serid;
                } pkg_header;

                memcpy(&pkg_header, _send.data + 4, sizeof(pkg_header));
                swWarn("fd=%d, worker=%d, index=%d, serid=%d", _send.info.fd, pkg_header.worker, pkg_header.index, pkg_header.serid);
#endif
                swReactorThread_send(&_send);
                worker->lock.unlock(&worker->lock);
            }
        }
        else if (errno == EAGAIN)
        {
            return SW_OK;
        }
        else
        {
            swWarn("read(worker_pipe) failed. Error: %s[%d]", strerror(errno), errno);
            return SW_ERR;
        }
    }
