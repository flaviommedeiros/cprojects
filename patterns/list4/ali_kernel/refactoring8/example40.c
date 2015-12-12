static int
snd_azf3328_codec_trigger(enum snd_azf3328_codec_type codec_type,
			struct snd_pcm_substream *substream, int cmd)
{
	struct snd_azf3328 *chip = snd_pcm_substream_chip(substream);
	const struct snd_azf3328_codec_data *codec = &chip->codecs[codec_type];
	struct snd_pcm_runtime *runtime = substream->runtime;
	int result = 0;
	u16 flags1;
	bool previously_muted = 0;
	bool is_playback_codec = (AZF_CODEC_PLAYBACK == codec_type);

	snd_azf3328_dbgcalls("snd_azf3328_codec_trigger cmd %d\n", cmd);

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
		snd_azf3328_dbgcodec("START %s\n", codec->name);

		if (is_playback_codec) {
			/* mute WaveOut (avoid clicking during setup) */
			previously_muted =
				snd_azf3328_mixer_set_mute(
						chip, IDX_MIXER_WAVEOUT, 1
				);
		}

		snd_azf3328_codec_setfmt(chip, codec_type,
			runtime->rate,
			snd_pcm_format_width(runtime->format),
			runtime->channels);

		spin_lock(&chip->reg_lock);
		/* first, remember current value: */
		flags1 = snd_azf3328_codec_inw(codec, IDX_IO_CODEC_DMA_FLAGS);

		/* stop transfer */
		flags1 &= ~DMA_RESUME;
		snd_azf3328_codec_outw(codec, IDX_IO_CODEC_DMA_FLAGS, flags1);

		/* FIXME: clear interrupts or what??? */
		snd_azf3328_codec_outw(codec, IDX_IO_CODEC_IRQTYPE, 0xffff);
		spin_unlock(&chip->reg_lock);

		snd_azf3328_codec_setdmaa(chip, codec_type, runtime->dma_addr,
			snd_pcm_lib_period_bytes(substream),
			snd_pcm_lib_buffer_bytes(substream)
		);

		spin_lock(&chip->reg_lock);
#ifdef WIN9X
		/* FIXME: enable playback/recording??? */
		flags1 |= DMA_RUN_SOMETHING1 | DMA_RUN_SOMETHING2;
		snd_azf3328_codec_outw(codec, IDX_IO_CODEC_DMA_FLAGS, flags1);

		/* start transfer again */
		/* FIXME: what is this value (0x0010)??? */
		flags1 |= DMA_RESUME | DMA_EPILOGUE_SOMETHING;
		snd_azf3328_codec_outw(codec, IDX_IO_CODEC_DMA_FLAGS, flags1);
#else /* NT4 */
		snd_azf3328_codec_outw(codec, IDX_IO_CODEC_DMA_FLAGS,
			0x0000);
		snd_azf3328_codec_outw(codec, IDX_IO_CODEC_DMA_FLAGS,
			DMA_RUN_SOMETHING1);
		snd_azf3328_codec_outw(codec, IDX_IO_CODEC_DMA_FLAGS,
			DMA_RUN_SOMETHING1 |
			DMA_RUN_SOMETHING2);
		snd_azf3328_codec_outw(codec, IDX_IO_CODEC_DMA_FLAGS,
			DMA_RESUME |
			SOMETHING_ALMOST_ALWAYS_SET |
			DMA_EPILOGUE_SOMETHING |
			DMA_SOMETHING_ELSE);
#endif
		spin_unlock(&chip->reg_lock);
		snd_azf3328_ctrl_codec_activity(chip, codec_type, 1);

		if (is_playback_codec) {
			/* now unmute WaveOut */
			if (!previously_muted)
				snd_azf3328_mixer_set_mute(
						chip, IDX_MIXER_WAVEOUT, 0
				);
		}

		snd_azf3328_dbgcodec("STARTED %s\n", codec->name);
		break;
	case SNDRV_PCM_TRIGGER_RESUME:
		snd_azf3328_dbgcodec("RESUME %s\n", codec->name);
		/* resume codec if we were active */
		spin_lock(&chip->reg_lock);
		if (codec->running)
			snd_azf3328_codec_outw(codec, IDX_IO_CODEC_DMA_FLAGS,
				snd_azf3328_codec_inw(
					codec, IDX_IO_CODEC_DMA_FLAGS
				) | DMA_RESUME
			);
		spin_unlock(&chip->reg_lock);
		break;
	case SNDRV_PCM_TRIGGER_STOP:
		snd_azf3328_dbgcodec("STOP %s\n", codec->name);

		if (is_playback_codec) {
			/* mute WaveOut (avoid clicking during setup) */
			previously_muted =
				snd_azf3328_mixer_set_mute(
						chip, IDX_MIXER_WAVEOUT, 1
				);
		}

		spin_lock(&chip->reg_lock);
		/* first, remember current value: */
		flags1 = snd_azf3328_codec_inw(codec, IDX_IO_CODEC_DMA_FLAGS);

		/* stop transfer */
		flags1 &= ~DMA_RESUME;
		snd_azf3328_codec_outw(codec, IDX_IO_CODEC_DMA_FLAGS, flags1);

		/* hmm, is this really required? we're resetting the same bit
		 * immediately thereafter... */
		flags1 |= DMA_RUN_SOMETHING1;
		snd_azf3328_codec_outw(codec, IDX_IO_CODEC_DMA_FLAGS, flags1);

		flags1 &= ~DMA_RUN_SOMETHING1;
		snd_azf3328_codec_outw(codec, IDX_IO_CODEC_DMA_FLAGS, flags1);
		spin_unlock(&chip->reg_lock);
		snd_azf3328_ctrl_codec_activity(chip, codec_type, 0);

		if (is_playback_codec) {
			/* now unmute WaveOut */
			if (!previously_muted)
				snd_azf3328_mixer_set_mute(
						chip, IDX_MIXER_WAVEOUT, 0
				);
		}

		snd_azf3328_dbgcodec("STOPPED %s\n", codec->name);
		break;
	case SNDRV_PCM_TRIGGER_SUSPEND:
		snd_azf3328_dbgcodec("SUSPEND %s\n", codec->name);
		/* make sure codec is stopped */
		snd_azf3328_codec_outw(codec, IDX_IO_CODEC_DMA_FLAGS,
			snd_azf3328_codec_inw(
				codec, IDX_IO_CODEC_DMA_FLAGS
			) & ~DMA_RESUME
		);
		break;
        case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		snd_printk(KERN_ERR "FIXME: SNDRV_PCM_TRIGGER_PAUSE_PUSH NIY!\n");
                break;
        case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		snd_printk(KERN_ERR "FIXME: SNDRV_PCM_TRIGGER_PAUSE_RELEASE NIY!\n");
                break;
        default:
		snd_printk(KERN_ERR "FIXME: unknown trigger mode!\n");
                return -EINVAL;
	}

	snd_azf3328_dbgcallleave();
	return result;
}
