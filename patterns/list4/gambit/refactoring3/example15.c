switch (he->h_addrtype)
        {
        case AF_INET:
          {
            x = ___in_addr_to_SCMOBJ
                  (___CAST(struct in_addr*,he->h_addr_list[i]),
                   ___RETURN_POS);
            break;
          }

#ifdef USE_IPV6
        case AF_INET6:
          {
            x = ___in6_addr_to_SCMOBJ
                  (___CAST(struct in6_addr*,he->h_addr_list[i]),
                   ___RETURN_POS);
            break;
          }

#endif

        default:
          continue; /* ignore unknown address families */
        }
