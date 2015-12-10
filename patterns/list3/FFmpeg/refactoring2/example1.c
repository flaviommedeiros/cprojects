#ifdef SOCK_CLOEXEC
if (fd == -1 && errno == EINVAL)
#endif
    {
        fd = socket(af, type, proto);
#if HAVE_FCNTL
        if (fd != -1) {
            if (fcntl(fd, F_SETFD, FD_CLOEXEC) == -1)
                av_log(NULL, AV_LOG_DEBUG, "Failed to set close on exec\n");
        }
#endif
    }
