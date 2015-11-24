#ifdef _WIN32
if (!lock->lock)
#else
   if (pthread_mutex_init(&lock->lock, NULL) < 0)
#endif
   {
      free(lock);
      return NULL;
   }
