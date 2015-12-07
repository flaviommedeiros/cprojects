#ifdef EPOLL_CLOEXEC
if (backend_fd < 0 && (errno == EINVAL || errno == ENOSYS))
#endif
    backend_fd = epoll_create (256);
