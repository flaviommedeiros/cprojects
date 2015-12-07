if ((select(ctxt->fd + 1, &rfd, NULL, NULL, &tv) < 1)
#if defined(EINTR)
            && (errno != EINTR)
#endif
            )
            return (0);
