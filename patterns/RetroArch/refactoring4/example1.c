#ifdef _WIN32
if (!thread->thread)
#else
   if (pthread_create(&thread->id, NULL, thread_wrap, data) < 0)
#endif
   {
      free(data);
      free(thread);
      return NULL;
   }
