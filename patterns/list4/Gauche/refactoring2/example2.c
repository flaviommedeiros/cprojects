#   ifndef GC_ANDROID_LOG
if (!GC_write_disabled)
#     endif
      {
        if (WRITE(GC_stderr, (void *)msg, strlen(msg)) >= 0)
          (void)WRITE(GC_stderr, (void *)("\n"), 1);
      }
