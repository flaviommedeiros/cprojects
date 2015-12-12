if (
#ifndef HAVE_isastream
          1
#else
          !isastream (fd)
#ifdef I_PUSH
          || (ioctl (fd, I_PUSH, "ptem") >= 0 &&
              ioctl (fd, I_PUSH, "ldterm") >= 0)
#endif
#endif
         )
        {
          *slave_fd = fd;
          return 0;
        }
