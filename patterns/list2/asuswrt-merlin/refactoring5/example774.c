#ifdef SIOCGIFINDEX
if ( 0 >= ioctl(sockfd, SIOCGIFINDEX, &ifrcopy))
            ifi->ifi_index = ifrcopy.ifr_index;
        else
#endif
            ifi->ifi_index = index++;
