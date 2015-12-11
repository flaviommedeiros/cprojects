#ifdef ENABLE_IPV6
if(*string_ftpport == '[') {
      /* [ipv6]:port(-range) */
      ip_start = string_ftpport + 1;
      if((ip_end = strchr(string_ftpport, ']')) != NULL )
        strncpy(addr, ip_start, ip_end - ip_start);
    }
    else
#endif
      if(*string_ftpport == ':') {
        /* :port */
        ip_end = string_ftpport;
    }
    else if((ip_end = strchr(string_ftpport, ':')) != NULL) {
        /* either ipv6 or (ipv4|domain|interface):port(-range) */
#ifdef ENABLE_IPV6
      if(Curl_inet_pton(AF_INET6, string_ftpport, sa6) == 1) {
        /* ipv6 */
        port_min = port_max = 0;
        strcpy(addr, string_ftpport);
        ip_end = NULL; /* this got no port ! */
      }
      else
#endif
        /* (ipv4|domain|interface):port(-range) */
        strncpy(addr, string_ftpport, ip_end - ip_start );
    }
    else
      /* ipv4|interface */
      strcpy(addr, string_ftpport);
