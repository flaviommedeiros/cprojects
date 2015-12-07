#ifdef FD_SETSIZE
if (fd < FD_SETSIZE)
#endif
        {
          FD_ZERO(&rfds);
          FD_SET(fd, &rfds);
          tv.tv_sec = delay;
          tv.tv_usec = delay? 0 : 100000;
          if ( !(rc=select(fd+1, &rfds, NULL, NULL, &tv)) )
            {
              if (!any_need_entropy || last_so_far != (want - length) )
                {
                  last_so_far = want - length;
                  _gcry_random_progress ("need_entropy", 'X',
                                         (int)last_so_far, (int)want);
                  any_need_entropy = 1;
                }
              delay = 3; /* Use 3 seconds henceforth.  */
              continue;
            }
          else if( rc == -1 )
            {
              log_error ("select() error: %s\n", strerror(errno));
              if (!delay)
                delay = 1; /* Use 1 second if we encounter an error before
                          we have ever blocked.  */
              continue;
            }
        }
