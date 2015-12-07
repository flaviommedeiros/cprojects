if (if_msg.ifm_data.ifi_lastchange.tv_sec == 0 &&
#if STRUCT_IFNET_HAS_IF_LASTCHANGE_TV_NSEC
            if_msg.ifm_data.ifi_lastchange.tv_nsec == 0
#else
            if_msg.ifm_data.ifi_lastchange.tv_usec == 0
#endif
           )
            long_return = 0;
        else if (if_msg.ifm_data.ifi_lastchange.tv_sec < starttime.tv_sec)
            long_return = 0;
        else {
            long_return = (u_long)
                ((if_msg.ifm_data.ifi_lastchange.tv_sec -
                  starttime.tv_sec) * 100 +
                 (
#if STRUCT_IFNET_HAS_IF_LASTCHANGE_TV_NSEC
                  if_msg.ifm_data.ifi_lastchange.tv_nsec / 1000
#else
                  if_msg.ifm_data.ifi_lastchange.tv_usec
#endif
                  - starttime.tv_usec) / 10000);
        }
