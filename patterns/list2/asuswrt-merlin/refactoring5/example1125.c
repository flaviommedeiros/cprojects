#ifndef HAVE_W32_SYSTEM
if (loop_mode && errno == EPIPE)
        loop_mode = 0;
      else
#endif
        die ("writing output failed: %s\n", strerror (errno));
