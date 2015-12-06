#if defined (MEMDBG_ON)
if (posix_memalign(&ptr, align, size))
		pexit("posix_memalign ("Zu" bytes)", size);
