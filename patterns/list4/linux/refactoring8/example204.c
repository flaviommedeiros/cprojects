static const unsigned short radio_addrs[] = {
#if IS_ENABLED(CONFIG_MEDIA_TUNER_TEA5761)
		0x10,
#endif
		0x60,
		I2C_CLIENT_END
	};
