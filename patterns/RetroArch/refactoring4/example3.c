#ifdef _WIN32
if (!cond->event)
#else
   if (pthread_cond_init(&cond->cond, NULL) < 0)
#endif
   {
      free(cond);
      return NULL;
   }
