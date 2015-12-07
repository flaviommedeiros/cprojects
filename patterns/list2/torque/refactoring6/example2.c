if (ai->ai_family != AF_INET 
#ifdef IPV6_V6ONLY
            && ai->ai_family != AF_INET6
#endif
        )
        continue;
