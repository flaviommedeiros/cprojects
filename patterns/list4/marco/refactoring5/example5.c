#ifdef HAVE_XSYNC
if (!window->disable_sync &&
      window->display->grab_sync_request_alarm != None)
    {
      if (window->sync_request_time.tv_sec != 0 ||
	  window->sync_request_time.tv_usec != 0)
	{
	  double elapsed =
	    time_diff (&current_time, &window->sync_request_time);

	  if (elapsed < 1000.0)
	    {
	      /* We want to be sure that the timeout happens at
	       * a time where elapsed will definitely be
	       * greater than 1000, so we can disable sync
	       */
	      if (remaining)
		*remaining = 1000.0 - elapsed + 100;

	      return FALSE;
	    }
	  else
	    {
	      /* We have now waited for more than a second for the
	       * application to respond to the sync request
	       */
	      window->disable_sync = TRUE;
	      return TRUE;
	    }
	}
      else
	{
	  /* No outstanding sync requests. Go ahead and resize
	   */
	  return TRUE;
	}
    }
  else
#endif /* HAVE_XSYNC */
    {
      const double max_resizes_per_second = 25.0;
      const double ms_between_resizes = 1000.0 / max_resizes_per_second;
      double elapsed;

      elapsed = time_diff (&current_time, &window->display->grab_last_moveresize_time);

      if (elapsed >= 0.0 && elapsed < ms_between_resizes)
	{
	  meta_topic (META_DEBUG_RESIZING,
		      "Delaying move/resize as only %g of %g ms elapsed\n",
		      elapsed, ms_between_resizes);

	  if (remaining)
	    *remaining = (ms_between_resizes - elapsed);

	  return FALSE;
	}

      meta_topic (META_DEBUG_RESIZING,
		  " Checked moveresize freq, allowing move/resize now (%g of %g seconds elapsed)\n",
		  elapsed / 1000.0, 1.0 / max_resizes_per_second);

      return TRUE;
    }
