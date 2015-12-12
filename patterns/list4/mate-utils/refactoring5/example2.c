#ifdef ENABLE_IPV6
if (priv->sockaddr.ss_family == AF_INET6)
    ((struct sockaddr_in6 *) &priv->sockaddr)->sin6_port = g_htons (priv->port);
  else
#endif
    ((struct sockaddr_in *) &priv->sockaddr)->sin_port = g_htons (priv->port);
