#ifdef USE_ONE_SIGNAL_HAND
if (sig != THR_SERVER_ALARM)
#endif
      printf("Main thread: Got signal %d\n",sig);
