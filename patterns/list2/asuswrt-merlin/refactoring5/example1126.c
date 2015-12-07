#ifdef HAVE_USLEEP
if (t < 1) {
                usleep(t * 1e6);
            }
            else
#endif
                sleep(t);
