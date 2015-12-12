static snd_pcm_format_t hpi_to_alsa_formats[] = {
	-1,			/* INVALID */
	SNDRV_PCM_FORMAT_U8,	/* HPI_FORMAT_PCM8_UNSIGNED        1 */
	SNDRV_PCM_FORMAT_S16,	/* HPI_FORMAT_PCM16_SIGNED         2 */
	-1,			/* HPI_FORMAT_MPEG_L1              3 */
	SNDRV_PCM_FORMAT_MPEG,	/* HPI_FORMAT_MPEG_L2              4 */
	SNDRV_PCM_FORMAT_MPEG,	/* HPI_FORMAT_MPEG_L3              5 */
	-1,			/* HPI_FORMAT_DOLBY_AC2            6 */
	-1,			/* HPI_FORMAT_DOLBY_AC3            7 */
	SNDRV_PCM_FORMAT_S16_BE,/* HPI_FORMAT_PCM16_BIGENDIAN      8 */
	-1,			/* HPI_FORMAT_AA_TAGIT1_HITS       9 */
	-1,			/* HPI_FORMAT_AA_TAGIT1_INSERTS   10 */
	SNDRV_PCM_FORMAT_S32,	/* HPI_FORMAT_PCM32_SIGNED        11 */
	-1,			/* HPI_FORMAT_RAW_BITSTREAM       12 */
	-1,			/* HPI_FORMAT_AA_TAGIT1_HITS_EX1  13 */
	SNDRV_PCM_FORMAT_FLOAT,	/* HPI_FORMAT_PCM32_FLOAT         14 */
#if 1
	/* ALSA can't handle 3 byte sample size together with power-of-2
	 *  constraint on buffer_bytes, so disable this format
	 */
	-1
#else
	/* SNDRV_PCM_FORMAT_S24_3LE */ /* HPI_FORMAT_PCM24_SIGNED 15 */
#endif
};
