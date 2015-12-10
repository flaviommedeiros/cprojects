switch (((struct sockaddr *)from)->sa_family) {
    case AF_INET:
        {
           const struct sockaddr_in*  src = from;

            if (fromlen < sizeof(*src))
                return set_errno(EINVAL);

            a->family         = SOCKET_INET;
            a->u.inet.port    = ntohs(src->sin_port);
            a->u.inet.address = ntohl(src->sin_addr.s_addr);
        }
        break;

#ifdef HAVE_IN6_SOCKETS
    case AF_INET6:
        {
            const struct sockaddr_in6*  src = from;

            if (fromlen < sizeof(*src))
                return set_errno(EINVAL);

            a->family     = SOCKET_IN6;
            a->u.in6.port = ntohs(src->sin6_port);
            memcpy(a->u.in6.address, src->sin6_addr.s6_addr, 16);
        }
        break;
#endif

#ifdef HAVE_UNIX_SOCKETS
    case AF_LOCAL:
        {
            const struct sockaddr_un*  src = from;
            char*                end;

            if (fromlen < sizeof(*src))
                return set_errno(EINVAL);

            /* check that the path is zero-terminated */
            end = memchr(src->sun_path, 0, UNIX_PATH_MAX);
            if (end == NULL)
                return set_errno(EINVAL);

            a->family = SOCKET_UNIX;
            a->u._unix.owner = 1;
            a->u._unix.path  = strdup(src->sun_path);
        }
        break;
#endif

    default:
        return set_errno(EINVAL);
    }
