switch (sa->sa_family) {
  case AF_INET:
    sa_length= sizeof (struct sockaddr_in);
#ifdef HAVE_SOCKADDR_IN_SIN_LEN
    ((struct sockaddr_in *) sa)->sin_len= sa_length;
#endif /* HAVE_SOCKADDR_IN_SIN_LEN */
    break;

#ifdef HAVE_IPV6
  case AF_INET6:
    sa_length= sizeof (struct sockaddr_in6);
# ifdef HAVE_SOCKADDR_IN6_SIN6_LEN
    ((struct sockaddr_in6 *) sa)->sin6_len= sa_length;
# endif /* HAVE_SOCKADDR_IN6_SIN6_LEN */
    break;
#endif /* HAVE_IPV6 */
  }
