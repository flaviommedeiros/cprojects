if(nread_socket <= 0
#ifdef USE_WINSOCK
       || FD_ISSET(sockfd, &fds_err)
#endif
       ) {
      logmsg("====> Client disconnect");
      if(!write_stdout("DISC\n", 5))
        return FALSE;
      sclose(sockfd);
      *sockfdp = CURL_SOCKET_BAD;
      if(*mode == PASSIVE_CONNECT)
        *mode = PASSIVE_LISTEN;
      else
        *mode = ACTIVE_DISCONNECT;
      return TRUE;
    }
