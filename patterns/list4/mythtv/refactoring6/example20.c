if (localaddr.ss_family != AF_INET
#if HAVE_STRUCT_SOCKADDR_IN6
        && localaddr.ss_family != AF_INET6
#endif
        ) {
        av_log(s, AV_LOG_ERROR, "Unsupported protocol family\n");
        ret = AVERROR(EIO);
        goto fail;
    }
