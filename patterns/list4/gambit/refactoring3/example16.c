switch (kind)
        {

#ifdef USE_NETWORKING

        case ___TCP_CLIENT_DEVICE_KIND:
          {
            ___device_tcp_client *d;
            struct sockaddr server_addr;

            if ((e = ___device_tcp_client_setup_from_socket
                       (&d,
                        dgroup,
                        fd,
                        &server_addr,
                        0,
                        0,
                        direction))
                == ___FIX(___NO_ERR))
              *dev = ___CAST(___device_stream*,d);

            break;
          }

#endif

        case ___FILE_DEVICE_KIND:
          {
            ___device_file *d;

#ifdef USE_NONBLOCKING_FILE_IO

            /*
             * Setup file descriptor to perform nonblocking I/O.
             */

            if (set_fd_blocking_mode (fd, 0) != 0) /* set nonblocking mode */
              return err_code_from_errno ();

#endif

            if ((e = ___device_file_setup_from_fd
                       (&d,
                        dgroup,
                        fd,
                        direction))
                == ___FIX(___NO_ERR))
              *dev = ___CAST(___device_stream*,d);

            break;
          }

        default:
          {
            e = ___FIX(___UNKNOWN_ERR);
            break;
          }
        }
