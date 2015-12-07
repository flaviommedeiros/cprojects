#  ifdef IN6_IS_ADDR_V4MAPPED
if (IN6_IS_ADDR_V4MAPPED(&data->peer.sa_in6.sin6_addr))
            /*
             * Assume this is UDP - 20 bytes for IP, 8 bytes for UDP
             */
            ret = 28;
        else
#  endif
            /*
             * Assume this is UDP - 40 bytes for IP, 8 bytes for UDP
             */
            ret = 48;
