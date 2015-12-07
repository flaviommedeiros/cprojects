#ifdef _POSIX_THREADS
if (nthreads > 0) {
		for (i = 0; i < nthreads; i++)
			DB_BENCH_ASSERT(pthread_create(&threads[i].id,
			    NULL, latch_threadmain, &threads[i]) == 0);
		for (i = 0; i < nthreads; i++) {
			ret = pthread_join(threads[i].id, &status);
			DB_BENCH_ASSERT(ret == 0);
			contended += threads[i].contentions;
		}

	} else
#endif
		contended = time_latches(dbenv, mutex, count);
