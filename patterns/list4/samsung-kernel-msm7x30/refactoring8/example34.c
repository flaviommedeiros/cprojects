int ct_alsa_pcm_create(struct ct_atc *atc,
		       enum CTALSADEVS device,
		       const char *device_name)
{
	struct snd_pcm *pcm;
	int err;
	int playback_count, capture_count;

	playback_count = (IEC958 == device) ? 1 : 256;
	capture_count = (FRONT == device) ? 1 : 0;
	err = snd_pcm_new(atc->card, "ctxfi", device,
			  playback_count, capture_count, &pcm);
	if (err < 0) {
		printk(KERN_ERR "ctxfi: snd_pcm_new failed!! Err=%d\n", err);
		return err;
	}

	pcm->private_data = atc;
	pcm->info_flags = 0;
	pcm->dev_subclass = SNDRV_PCM_SUBCLASS_GENERIC_MIX;
	strlcpy(pcm->name, device_name, sizeof(pcm->name));

	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &ct_pcm_playback_ops);

	if (FRONT == device)
		snd_pcm_set_ops(pcm,
				SNDRV_PCM_STREAM_CAPTURE, &ct_pcm_capture_ops);

	snd_pcm_lib_preallocate_pages_for_all(pcm, SNDRV_DMA_TYPE_DEV_SG,
			snd_dma_pci_data(atc->pci), 128*1024, 128*1024);

#ifdef CONFIG_PM
	atc->pcms[device] = pcm;
#endif

	return 0;
}
