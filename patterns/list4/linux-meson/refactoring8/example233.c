static struct ParameterData cfg_data[] = {
	{ /* adapter id */
		CFG_PARAM_UNSET,
		0,
		15,
		7,
		7
	},
	{ /* max speed */
		CFG_PARAM_UNSET,
		  0,
		  7,
		  1,	/* 13.3Mhz */
		  4,	/*  6.7Hmz */
	},
	{ /* dev mode */
		CFG_PARAM_UNSET,
		0,
		0x3f,
		NTC_DO_PARITY_CHK | NTC_DO_DISCONNECT | NTC_DO_SYNC_NEGO |
			NTC_DO_WIDE_NEGO | NTC_DO_TAG_QUEUEING |
			NTC_DO_SEND_START,
		NTC_DO_PARITY_CHK | NTC_DO_SEND_START
	},
	{ /* adapter mode */
		CFG_PARAM_UNSET,
		0,
		0x2f,
#ifdef CONFIG_SCSI_MULTI_LUN
			NAC_SCANLUN |
#endif
		NAC_GT2DRIVES | NAC_GREATER_1G | NAC_POWERON_SCSI_RESET
			/*| NAC_ACTIVE_NEG*/,
		NAC_GT2DRIVES | NAC_GREATER_1G | NAC_POWERON_SCSI_RESET | 0x08
	},
	{ /* tags */
		CFG_PARAM_UNSET,
		0,
		5,
		3,	/* 16 tags (??) */
		2,
	},
	{ /* reset delay */
		CFG_PARAM_UNSET,
		0,
		180,
		1,	/* 1 second */
		10,	/* 10 seconds */
	}
};
