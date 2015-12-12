#ifdef _WIN32
if (revents & POLLOUT || revents & POLLWRNORM) {
#else
    if (revents & POLLOUT) {
#endif
        /* First, POLLOUT is a sign we may be connected */
        if (s->state == SSH_SOCKET_CONNECTING) {
            SSH_LOG(SSH_LOG_PACKET, "Received POLLOUT in connecting state");
            s->state = SSH_SOCKET_CONNECTED;
            if (p != NULL) {
                ssh_poll_set_events(p, POLLOUT | POLLIN);
            }
            r = ssh_socket_set_blocking(ssh_socket_get_fd_in(s));
            if (r < 0) {
                return -1;
            }
            if (s->callbacks && s->callbacks->connected) {
                s->callbacks->connected(SSH_SOCKET_CONNECTED_OK, 0,
                                        s->callbacks->userdata);
            }
            return 0;
        }
        /* So, we can write data */
        s->write_wontblock=1;
        if (p != NULL) {
            ssh_poll_remove_events(p, POLLOUT);
        }

        /* If buffered data is pending, write it */
        if (buffer_get_rest_len(s->out_buffer) > 0) {
            ssh_socket_nonblocking_flush(s);
        } else if (s->callbacks && s->callbacks->controlflow) {
            /* Otherwise advertise the upper level that write can be done */
            s->callbacks->controlflow(SSH_SOCKET_FLOW_WRITEWONTBLOCK,
                                      s->callbacks->userdata);
        }
        /* TODO: Find a way to put back POLLOUT when buffering occurs */
    }
    /* Return -1 if one of the poll handlers disappeared */
    return (s->poll_in == NULL || s->poll_out == NULL) ? -1 : 0;
}
