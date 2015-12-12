if ((rtc_args->proc == TIMEREMOTE_PROCEEDURE_GET_JULIAN)
#ifdef CONFIG_RTC_SECURE_TIME_SUPPORT
	|| (rtc_args->proc == TIMEREMOTE_PROCEEDURE_GET_SECURE_JULIAN)
#endif
	) {
		*(uint32_t *)buff = (uint32_t) cpu_to_be32(0x1);

		return sizeof(uint32_t);
	} else
		return 0;
