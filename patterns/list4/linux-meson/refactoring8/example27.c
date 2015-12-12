static struct snd_soc_card aml_snd_soc_card = {
    //.name = "AML-RT5631",
    .driver_name = "SOC-Audio",
    .dai_link = &aml_codec_dai_link[0],
    .num_links = ARRAY_SIZE(aml_codec_dai_link),
    .set_bias_level = aml_set_bias_level,
#ifdef CONFIG_PM_SLEEP
	.suspend_pre    = aml_suspend_pre,
	.suspend_post   = aml_suspend_post,
	.resume_pre     = aml_resume_pre,
	.resume_post    = aml_resume_post,
#endif
};
