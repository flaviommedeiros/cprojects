if (setsid () >= 0 &&
#ifdef TIOCSCTTY
          ioctl (fdp->input.reading_fd, TIOCSCTTY, 0) >= 0 &&
#endif
          open_pseudo_terminal_slave (fdp->input.writing_fd,
                                      &fdp->input.reading_fd) >= 0)
        {
          int tmp;
          if (setup_terminal_slave (fdp->input.reading_fd) >= 0 &&
              (fdp->output.writing_fd = dup_no_EINTR (fdp->input.reading_fd)) >= 0)
            return 0;
          tmp = errno;
          close_no_EINTR (fdp->input.reading_fd); /* ignore error */
          errno = tmp;
        }
