if (sendto(netplay->udp_fd, (const char*)netplay->packet_buffer,
               sizeof(netplay->packet_buffer), 0, addr,
#ifdef ANDROID
               sizeof(struct sockaddr_in6)
#else
               sizeof(struct sockaddr_in)
#endif
         )
            != sizeof(netplay->packet_buffer))
      {
         warn_hangup();
         netplay->has_connection = false;
         return false;
      }
