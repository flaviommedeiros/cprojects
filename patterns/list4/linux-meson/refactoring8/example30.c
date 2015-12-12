static struct snd_soc_card snd_soc_rt3261 = {
    .name = "AML-RT3261",
    .driver_name = "SOC-Audio",
    .dai_link = &rt3261_dai_link[0],
    .num_links = ARRAY_SIZE(rt3261_dai_link),
    .set_bias_level = rt3261_set_bias_level,
#ifdef CONFIG_PM_SLEEP
	.suspend_pre    = rt3261_suspend_pre,
	.suspend_post   = rt3261_suspend_post,
	.resume_pre     = rt3261_resume_pre,
	.resume_post    = rt3261_resume_post,
#endif
//	.pop_time 		= POP_TIME,   //add by jf.s for power up/down widgets
};
