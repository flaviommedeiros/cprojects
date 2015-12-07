if(pthread_create(&pThis->writerThreadID,
#ifdef HAVE_PTHREAD_SETSCHEDPARAM
			    	  &default_thread_attr,
#else
				  NULL,
#endif
				  asyncWriterThread, pThis) != 0)
			DBGPRINTF("ERROR: stream %p cold not create writer thread\n", pThis);
