#ifdef ENABLE_SOCKS
if (sock->socks_proxy && sock->info.proto == PROTO_UDPv4)
          socket_bind (sock->ctrl_sd, &sock->info.lsa->local, "SOCKS");
      else
#endif
          socket_bind (sock->sd, &sock->info.lsa->local, "TCP/UDP");
