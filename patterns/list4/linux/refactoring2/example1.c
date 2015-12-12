#if IS_ENABLED(CONFIG_SND_PCM_OSS)
if (!substream->oss.oss)
#endif
		if (atomic_read(&substream->mmap_count))
			return -EBADFD;
