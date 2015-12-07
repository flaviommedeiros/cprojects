if ((opt.lfilename
#ifdef HAVE_ISATTY
       /* The progress bar doesn't make sense if the output is not a
          TTY -- when logging to file, it is better to review the
          dots.  */
       || !isatty (fileno (stderr))
#endif
       /* Normally we don't depend on terminal type because the
          progress bar only uses ^M to move the cursor to the
          beginning of line, which works even on dumb terminals.  But
          Jamie Zawinski reports that ^M and ^H tricks don't work in
          Emacs shell buffers, and only make a mess.  */
       || (term && 0 == strcmp (term, "emacs"))
       )
      && !current_impl_locked)
    {
      /* We're not printing to a TTY, so revert to the fallback
         display.  #### We're recursively calling
         set_progress_implementation here, which is slightly kludgy.
         It would be nicer if we provided that function a return value
         indicating a failure of some sort.  */
      set_progress_implementation (FALLBACK_PROGRESS_IMPLEMENTATION);
      return;
    }
