#ifdef HAVE_NET_IF_UTUN_H
if (tt->is_utun)
    return read_tun_header (tt, buf, len);
  else
#endif
    return read (tt->fd, buf, len);
