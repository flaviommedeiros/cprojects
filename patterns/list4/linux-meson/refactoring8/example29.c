static struct snd_soc_dai_link rt3261_dai_link[] = {
    {
        .name = "RT3261",
        .stream_name = "RT3261 PCM",
        .cpu_dai_name = "aml-dai0",
        .codec_dai_name = "rt3261-aif1",
        .init = rt3261_codec_init,
        .platform_name = "aml-audio.0",
        .codec_name = "rt3261.1-001c",
        .ops = &rt3261_soc_ops,
    },
#if 1 //add jf.s
    {
        .name = "RT3261_BT_VOICE",
        .stream_name = "RT3261 BT PCM",
        .cpu_dai_name = "aml-dai0",
        .codec_dai_name = "rt3261-aif2",
        .init = rt3261_codec_init2,
        .platform_name = "aml-audio.0",
        .codec_name = "rt3261.1-001c",
        .ops = &rt3261_voice_ops,
    },
#endif
};
