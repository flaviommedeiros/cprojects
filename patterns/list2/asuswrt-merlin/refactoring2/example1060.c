# if EV_USE_EVENTFD
if (fds [1] < 0 && errno == EINVAL)
        fds [1] = eventfd (0, 0);
