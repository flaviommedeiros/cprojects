if ((poll(&p, 1, timeout * 1000) < 1)
#if defined(EINTR)
            && (errno != EINTR)
#endif
            )
            return (0);
