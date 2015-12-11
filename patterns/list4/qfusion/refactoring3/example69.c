switch (cmd) {
    case BIO_CTRL_RESET:
        num = 0;
    case BIO_C_FILE_SEEK:
        ret = 0;
        break;
    case BIO_C_FILE_TELL:
    case BIO_CTRL_INFO:
        ret = 0;
        break;
    case BIO_C_SET_FD:
        dgram_clear(b);
        b->num = *((int *)ptr);
        b->shutdown = (int)num;
        b->init = 1;
        break;
    case BIO_C_GET_FD:
        if (b->init) {
            ip = (int *)ptr;
            if (ip != NULL)
                *ip = b->num;
            ret = b->num;
        } else
            ret = -1;
        break;
    case BIO_CTRL_GET_CLOSE:
        ret = b->shutdown;
        break;
    case BIO_CTRL_SET_CLOSE:
        b->shutdown = (int)num;
        break;
    case BIO_CTRL_PENDING:
    case BIO_CTRL_WPENDING:
        ret = 0;
        break;
    case BIO_CTRL_DUP:
    case BIO_CTRL_FLUSH:
        ret = 1;
        break;
    case BIO_CTRL_DGRAM_CONNECT:
        to = (struct sockaddr *)ptr;
# if 0
        if (connect(b->num, to, sizeof(struct sockaddr)) < 0) {
            perror("connect");
            ret = 0;
        } else {
# endif
            switch (to->sa_family) {
            case AF_INET:
                memcpy(&data->peer, to, sizeof(data->peer.sa_in));
                break;
# if OPENSSL_USE_IPV6
            case AF_INET6:
                memcpy(&data->peer, to, sizeof(data->peer.sa_in6));
                break;
# endif
            default:
                memcpy(&data->peer, to, sizeof(data->peer.sa));
                break;
            }
# if 0
        }
# endif
        break;
        /* (Linux)kernel sets DF bit on outgoing IP packets */
    case BIO_CTRL_DGRAM_MTU_DISCOVER:
# if defined(OPENSSL_SYS_LINUX) && defined(IP_MTU_DISCOVER) && defined(IP_PMTUDISC_DO)
        addr_len = (socklen_t) sizeof(addr);
        memset((void *)&addr, 0, sizeof(addr));
        if (getsockname(b->num, &addr.sa, &addr_len) < 0) {
            ret = 0;
            break;
        }
        switch (addr.sa.sa_family) {
        case AF_INET:
            sockopt_val = IP_PMTUDISC_DO;
            if ((ret = setsockopt(b->num, IPPROTO_IP, IP_MTU_DISCOVER,
                                  &sockopt_val, sizeof(sockopt_val))) < 0)
                perror("setsockopt");
            break;
#  if OPENSSL_USE_IPV6 && defined(IPV6_MTU_DISCOVER) && defined(IPV6_PMTUDISC_DO)
        case AF_INET6:
            sockopt_val = IPV6_PMTUDISC_DO;
            if ((ret = setsockopt(b->num, IPPROTO_IPV6, IPV6_MTU_DISCOVER,
                                  &sockopt_val, sizeof(sockopt_val))) < 0)
                perror("setsockopt");
            break;
#  endif
        default:
            ret = -1;
            break;
        }
        ret = -1;
# else
        break;
# endif
    case BIO_CTRL_DGRAM_QUERY_MTU:
# if defined(OPENSSL_SYS_LINUX) && defined(IP_MTU)
        addr_len = (socklen_t) sizeof(addr);
        memset((void *)&addr, 0, sizeof(addr));
        if (getsockname(b->num, &addr.sa, &addr_len) < 0) {
            ret = 0;
            break;
        }
        sockopt_len = sizeof(sockopt_val);
        switch (addr.sa.sa_family) {
        case AF_INET:
            if ((ret =
                 getsockopt(b->num, IPPROTO_IP, IP_MTU, (void *)&sockopt_val,
                            &sockopt_len)) < 0 || sockopt_val < 0) {
                ret = 0;
            } else {
                /*
                 * we assume that the transport protocol is UDP and no IP
                 * options are used.
                 */
                data->mtu = sockopt_val - 8 - 20;
                ret = data->mtu;
            }
            break;
#  if OPENSSL_USE_IPV6 && defined(IPV6_MTU)
        case AF_INET6:
            if ((ret =
                 getsockopt(b->num, IPPROTO_IPV6, IPV6_MTU,
                            (void *)&sockopt_val, &sockopt_len)) < 0
                || sockopt_val < 0) {
                ret = 0;
            } else {
                /*
                 * we assume that the transport protocol is UDP and no IPV6
                 * options are used.
                 */
                data->mtu = sockopt_val - 8 - 40;
                ret = data->mtu;
            }
            break;
#  endif
        default:
            ret = 0;
            break;
        }
# else
        ret = 0;
# endif
        break;
    case BIO_CTRL_DGRAM_GET_FALLBACK_MTU:
        ret = -dgram_get_mtu_overhead(data);
        switch (data->peer.sa.sa_family) {
        case AF_INET:
            ret += 576;
            break;
# if OPENSSL_USE_IPV6
        case AF_INET6:
#  ifdef IN6_IS_ADDR_V4MAPPED
            if (IN6_IS_ADDR_V4MAPPED(&data->peer.sa_in6.sin6_addr))
                ret += 576;
            else
#  endif
                ret += 1280;
            break;
# endif
        default:
            ret += 576;
            break;
        }
        break;
    case BIO_CTRL_DGRAM_GET_MTU:
        return data->mtu;
        break;
    case BIO_CTRL_DGRAM_SET_MTU:
        data->mtu = num;
        ret = num;
        break;
    case BIO_CTRL_DGRAM_SET_CONNECTED:
        to = (struct sockaddr *)ptr;

        if (to != NULL) {
            data->connected = 1;
            switch (to->sa_family) {
            case AF_INET:
                memcpy(&data->peer, to, sizeof(data->peer.sa_in));
                break;
# if OPENSSL_USE_IPV6
            case AF_INET6:
                memcpy(&data->peer, to, sizeof(data->peer.sa_in6));
                break;
# endif
            default:
                memcpy(&data->peer, to, sizeof(data->peer.sa));
                break;
            }
        } else {
            data->connected = 0;
            memset(&(data->peer), 0x00, sizeof(data->peer));
        }
        break;
    case BIO_CTRL_DGRAM_GET_PEER:
        switch (data->peer.sa.sa_family) {
        case AF_INET:
            ret = sizeof(data->peer.sa_in);
            break;
# if OPENSSL_USE_IPV6
        case AF_INET6:
            ret = sizeof(data->peer.sa_in6);
            break;
# endif
        default:
            ret = sizeof(data->peer.sa);
            break;
        }
        if (num == 0 || num > ret)
            num = ret;
        memcpy(ptr, &data->peer, (ret = num));
        break;
    case BIO_CTRL_DGRAM_SET_PEER:
        to = (struct sockaddr *)ptr;
        switch (to->sa_family) {
        case AF_INET:
            memcpy(&data->peer, to, sizeof(data->peer.sa_in));
            break;
# if OPENSSL_USE_IPV6
        case AF_INET6:
            memcpy(&data->peer, to, sizeof(data->peer.sa_in6));
            break;
# endif
        default:
            memcpy(&data->peer, to, sizeof(data->peer.sa));
            break;
        }
        break;
    case BIO_CTRL_DGRAM_SET_NEXT_TIMEOUT:
        memcpy(&(data->next_timeout), ptr, sizeof(struct timeval));
        break;
# if defined(SO_RCVTIMEO)
    case BIO_CTRL_DGRAM_SET_RECV_TIMEOUT:
#  ifdef OPENSSL_SYS_WINDOWS
        {
            struct timeval *tv = (struct timeval *)ptr;
            int timeout = tv->tv_sec * 1000 + tv->tv_usec / 1000;
            if (setsockopt(b->num, SOL_SOCKET, SO_RCVTIMEO,
                           (void *)&timeout, sizeof(timeout)) < 0) {
                perror("setsockopt");
                ret = -1;
            }
        }
#  else
        if (setsockopt(b->num, SOL_SOCKET, SO_RCVTIMEO, ptr,
                       sizeof(struct timeval)) < 0) {
            perror("setsockopt");
            ret = -1;
        }
#  endif
        break;
    case BIO_CTRL_DGRAM_GET_RECV_TIMEOUT:
        {
            union {
                size_t s;
                int i;
            } sz = {
                0
            };
#  ifdef OPENSSL_SYS_WINDOWS
            int timeout;
            struct timeval *tv = (struct timeval *)ptr;

            sz.i = sizeof(timeout);
            if (getsockopt(b->num, SOL_SOCKET, SO_RCVTIMEO,
                           (void *)&timeout, &sz.i) < 0) {
                perror("getsockopt");
                ret = -1;
            } else {
                tv->tv_sec = timeout / 1000;
                tv->tv_usec = (timeout % 1000) * 1000;
                ret = sizeof(*tv);
            }
#  else
            sz.i = sizeof(struct timeval);
            if (getsockopt(b->num, SOL_SOCKET, SO_RCVTIMEO,
                           ptr, (void *)&sz) < 0) {
                perror("getsockopt");
                ret = -1;
            } else if (sizeof(sz.s) != sizeof(sz.i) && sz.i == 0) {
                OPENSSL_assert(sz.s <= sizeof(struct timeval));
                ret = (int)sz.s;
            } else
                ret = sz.i;
#  endif
        }
        break;
# endif
# if defined(SO_SNDTIMEO)
    case BIO_CTRL_DGRAM_SET_SEND_TIMEOUT:
#  ifdef OPENSSL_SYS_WINDOWS
        {
            struct timeval *tv = (struct timeval *)ptr;
            int timeout = tv->tv_sec * 1000 + tv->tv_usec / 1000;
            if (setsockopt(b->num, SOL_SOCKET, SO_SNDTIMEO,
                           (void *)&timeout, sizeof(timeout)) < 0) {
                perror("setsockopt");
                ret = -1;
            }
        }
#  else
        if (setsockopt(b->num, SOL_SOCKET, SO_SNDTIMEO, ptr,
                       sizeof(struct timeval)) < 0) {
            perror("setsockopt");
            ret = -1;
        }
#  endif
        break;
    case BIO_CTRL_DGRAM_GET_SEND_TIMEOUT:
        {
            union {
                size_t s;
                int i;
            } sz = {
                0
            };
#  ifdef OPENSSL_SYS_WINDOWS
            int timeout;
            struct timeval *tv = (struct timeval *)ptr;

            sz.i = sizeof(timeout);
            if (getsockopt(b->num, SOL_SOCKET, SO_SNDTIMEO,
                           (void *)&timeout, &sz.i) < 0) {
                perror("getsockopt");
                ret = -1;
            } else {
                tv->tv_sec = timeout / 1000;
                tv->tv_usec = (timeout % 1000) * 1000;
                ret = sizeof(*tv);
            }
#  else
            sz.i = sizeof(struct timeval);
            if (getsockopt(b->num, SOL_SOCKET, SO_SNDTIMEO,
                           ptr, (void *)&sz) < 0) {
                perror("getsockopt");
                ret = -1;
            } else if (sizeof(sz.s) != sizeof(sz.i) && sz.i == 0) {
                OPENSSL_assert(sz.s <= sizeof(struct timeval));
                ret = (int)sz.s;
            } else
                ret = sz.i;
#  endif
        }
        break;
# endif
    case BIO_CTRL_DGRAM_GET_SEND_TIMER_EXP:
        /* fall-through */
    case BIO_CTRL_DGRAM_GET_RECV_TIMER_EXP:
# ifdef OPENSSL_SYS_WINDOWS
        if (data->_errno == WSAETIMEDOUT)
# else
        if (data->_errno == EAGAIN)
# endif
        {
            ret = 1;
            data->_errno = 0;
        } else
            ret = 0;
        break;
# ifdef EMSGSIZE
    case BIO_CTRL_DGRAM_MTU_EXCEEDED:
        if (data->_errno == EMSGSIZE) {
            ret = 1;
            data->_errno = 0;
        } else
            ret = 0;
        break;
# endif
    case BIO_CTRL_DGRAM_GET_MTU_OVERHEAD:
        ret = dgram_get_mtu_overhead(data);
        break;
    default:
        ret = 0;
        break;
    }
