static snd_pcm_uframes_t
snd_azf3328_codec_pointer(struct snd_pcm_substream *substream,
			  enum snd_azf3328_codec_type codec_type
)
{
	const struct snd_azf3328 *chip = snd_pcm_substream_chip(substream);
	const struct snd_azf3328_codec_data *codec = &chip->codecs[codec_type];
	unsigned long bufptr, result;
	snd_pcm_uframes_t frmres;

#ifdef QUERY_HARDWARE
	bufptr = snd_azf3328_codec_inl(codec, IDX_IO_CODEC_DMA_START_1);
#else
	bufptr = substream->runtime->dma_addr;
#endif
	result = snd_azf3328_codec_inl(codec, IDX_IO_CODEC_DMA_CURRPOS);

	/* calculate offset */
	result -= bufptr;
	frmres = bytes_to_frames( substream->runtime, result);
	snd_azf3328_dbgcodec("%s @ 0x%8lx, frames %8ld\n",
				codec->name, result, frmres);
	return frmres;
}
