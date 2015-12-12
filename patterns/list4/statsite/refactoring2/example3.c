#ifdef EPOLL_CLOEXEC
if (backend_fd < 0)
#endif
    backend_fd = epoll_create (256);
