static const char *gconfs[] = {
		"message.max.bytes", "12345", /* int property */
		"client.id", "my id", /* string property */
		"debug", "topic,metadata", /* S2F property */
#if WITH_ZLIB
		"compression.codec", "gzip", /* S2I property */
#endif
		NULL
	};
