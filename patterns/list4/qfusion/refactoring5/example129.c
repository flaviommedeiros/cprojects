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
