#ifdef AF_INET6
if (fsa->sa_family == AF_INET6) {
        struct sockaddr_in6 *sa6 = (struct sockaddr_in6*)(fsa);
        addr = &(sa6->sin6_addr);
    } else
#endif
    {
        struct sockaddr_in *sa = (struct sockaddr_in*)(fsa);
        addr = &(sa->sin_addr);
    }
