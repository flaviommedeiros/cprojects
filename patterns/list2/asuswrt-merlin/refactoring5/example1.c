#ifdef __COPY_CONTEXT_SIZE
if (have_saved_context)
	{
	  /* Lie about where the program actually is stopped since cygwin has informed us that
	     we should consider the signal to have occurred at another location which is stored
	     in "saved_context. */
	  memcpy (&current_thread->context, &saved_context, __COPY_CONTEXT_SIZE);
	  have_saved_context = 0;
	}
      else
#endif
	{
	  thread_info *th = current_thread;
	  th->context.ContextFlags = CONTEXT_DEBUGGER_DR;
	  GetThreadContext (th->h, &th->context);
	  /* Copy dr values from that thread.  */
	  dr[0] = th->context.Dr0;
	  dr[1] = th->context.Dr1;
	  dr[2] = th->context.Dr2;
	  dr[3] = th->context.Dr3;
	  dr[6] = th->context.Dr6;
	  dr[7] = th->context.Dr7;
	}
