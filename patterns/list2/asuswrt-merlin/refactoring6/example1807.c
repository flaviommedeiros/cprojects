if (1
#ifdef HAVE_ISATTY
          && isatty (fileno (logfp))
#endif
          )
        {
          /* If the output is a TTY, enable save context, i.e. store
             the most recent several messages ("context") and dump
             them to a log file in case SIGHUP or SIGUSR1 is received
             (or Ctrl+Break is pressed under Windows).  */
          save_context_p = true;
        }
