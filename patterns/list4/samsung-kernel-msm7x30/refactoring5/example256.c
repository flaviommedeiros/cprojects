#ifdef CONFIG_SND_SOC_MSM8660_APQ
if (machine_is_msm8x60_dragon())
			platform_add_devices(dragon_alsa_devices,
					ARRAY_SIZE(dragon_alsa_devices));
		else
#endif
			platform_add_devices(asoc_devices,
					ARRAY_SIZE(asoc_devices));
