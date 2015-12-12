static const unsigned short radio_addrs[] = {
#if defined(CONFIG_MEDIA_TUNER_TEA5761) || defined(CONFIG_MEDIA_TUNER_TEA5761_MODULE)
		0x10,
#endif
		0x60,
		I2C_CLIENT_END
	};
