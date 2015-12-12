static struct snd_soc_dai_link aml_codec_dai_link[] = {
    {
        .name = "SND_M8",
        .stream_name = "AML PCM",
        .cpu_dai_name = "aml-i2s-dai.0",
        .init = aml_asoc_init,
        .platform_name = "aml-i2s.0",
        //.codec_name = "aml_m8_codec.0",
        .ops = &aml_asoc_ops,
    },
#ifdef CONFIG_SND_SOC_PCM2BT
    {
        .name = "BT Voice",
        .stream_name = "Voice PCM",
        .cpu_dai_name = "aml-pcm-dai.0",
        .codec_dai_name = "pcm2bt-pcm",
        .platform_name = "aml-pcm.0",
        .codec_name = "pcm2bt.0",
        //.ops = &voice_soc_ops,
    },
#endif

    {
        .name = "AML-SPDIF",
        .stream_name = "SPDIF PCM",
        .cpu_dai_name = "aml-spdif-dai.0",
        .codec_dai_name = "dit-hifi",
        .init = NULL,
        .platform_name = "aml-i2s.0",
        .codec_name = "spdif-dit.0",
        .ops = NULL,      
    }, 

};
