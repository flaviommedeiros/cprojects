#if defined(CONFIG_SND_PCM_OSS) || defined(CONFIG_SND_PCM_OSS_MODULE)
if (!substream->oss.oss)
#endif
		if (atomic_read(&substream->mmap_count))
			return -EBADFD;
