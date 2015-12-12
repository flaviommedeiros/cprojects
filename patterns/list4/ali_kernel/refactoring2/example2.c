#if defined(CONFIG_SND_PCM_OSS) || defined(CONFIG_SND_PCM_OSS_MODULE)
if (!((struct snd_pcm_substream2 *)substream)->oss.oss)
#endif
		if (atomic_read(&substream->mmap_count))
			return -EBADFD;
