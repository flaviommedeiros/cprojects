static struct snd_soc_dai_link dummy_codec_dai_link[] = {
    {
        .name = "DUMMY_CODEC",
        .stream_name = "DUMMY_CODEC PCM",
        .cpu_dai_name = "aml-dai0",
        .codec_dai_name = "dummy_codec",
        .init = dummy_codec_codec_init,
        .platform_name = "aml-audio.0",
        .codec_name = "dummy_codec.0",
        .ops = &dummy_codec_soc_ops,
    },
#ifdef CONFIG_SND_SOC_PCM2BT
    {
        .name = "BT Voice",
        .stream_name = "Voice PCM",
        .cpu_dai_name = "aml-dai1",
        .codec_dai_name = "pcm2bt-pcm",
        .platform_name = "aml-audio.0",
        .codec_name = "pcm2bt.0",
        //.ops = &voice_soc_ops,
    },
#endif
};
