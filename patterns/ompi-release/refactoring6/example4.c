if (AF_INET != my_ss.ss_family
#if OPAL_ENABLE_IPV6
            && AF_INET6 != my_ss.ss_family
#endif
            ) {
            continue;
        }
