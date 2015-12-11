#ifdef ENABLE_IPV6
if(af == AF_INET6) {
      si6->sin6_family = AF_INET6;
      si6->sin6_port = htons(port);
      sizeof_sa = sizeof(struct sockaddr_in6);
    }
    else
#endif
    if(af == AF_INET) {
      si4->sin_family = AF_INET;
      si4->sin_port = htons(port);
      sizeof_sa = sizeof(struct sockaddr_in);
    }
