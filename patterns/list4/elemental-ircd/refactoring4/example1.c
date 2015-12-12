#ifdef HAVE_SOCKETPAIR
if(socketpair(family, sock_type, proto, nfd))
#else
    if(sock_type == SOCK_DGRAM) {
        return rb_inet_socketpair_udp(F1, F2);
    }
