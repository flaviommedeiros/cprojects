static const struct ieee1394_device_id fwnet_id_table[] = {
	{
		.match_flags  = IEEE1394_MATCH_SPECIFIER_ID |
				IEEE1394_MATCH_VERSION,
		.specifier_id = IANA_SPECIFIER_ID,
		.version      = RFC2734_SW_VERSION,
	},
#if IS_ENABLED(CONFIG_IPV6)
	{
		.match_flags  = IEEE1394_MATCH_SPECIFIER_ID |
				IEEE1394_MATCH_VERSION,
		.specifier_id = IANA_SPECIFIER_ID,
		.version      = RFC3146_SW_VERSION,
	},
#endif
	{ }
};
