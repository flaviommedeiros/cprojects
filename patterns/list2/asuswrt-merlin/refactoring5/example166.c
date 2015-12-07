#ifdef HAVE_NET_IF_UTUN_H
if (tt->is_utun)
    return write_tun_header (tt, buf, len);
  else
#endif
    return write (tt->fd, buf, len);
