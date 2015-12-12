if (dontblock
#if LWIP_SO_SNDTIMEO
        || (conn->send_timeout != 0)
#endif /* LWIP_SO_SNDTIMEO */
       ) {
      /* nonblocking write: maybe the data has been sent partly */
      *bytes_written = msg.msg.msg.w.len;
    } else {
      /* blocking call succeeded: all data has been sent if it */
      *bytes_written = size;
    }
