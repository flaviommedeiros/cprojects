if ((rtc_args->proc == TIMEREMOTE_PROCEEDURE_SET_JULIAN)
#ifdef CONFIG_RTC_SECURE_TIME_SUPPORT
	|| (rtc_args->proc == TIMEREMOTE_PROCEEDURE_SET_SECURE_JULIAN)
#endif
	) {
		struct timeremote_set_julian_req {
			uint32_t opt_arg;
			struct rpc_time_julian time;
		};
		struct timeremote_set_julian_req *set_req = buff;

		set_req->opt_arg = cpu_to_be32(0x1);
		set_req->time.year = cpu_to_be32(rtc_args->tm->tm_year);
		set_req->time.month = cpu_to_be32(rtc_args->tm->tm_mon + 1);
		set_req->time.day = cpu_to_be32(rtc_args->tm->tm_mday);
		set_req->time.hour = cpu_to_be32(rtc_args->tm->tm_hour);
		set_req->time.minute = cpu_to_be32(rtc_args->tm->tm_min);
		set_req->time.second = cpu_to_be32(rtc_args->tm->tm_sec);
		set_req->time.day_of_week = cpu_to_be32(rtc_args->tm->tm_wday);

		return sizeof(*set_req);

	} else if ((rtc_args->proc == TIMEREMOTE_PROCEEDURE_GET_JULIAN)
#ifdef CONFIG_RTC_SECURE_TIME_SUPPORT
	|| (rtc_args->proc == TIMEREMOTE_PROCEEDURE_GET_SECURE_JULIAN)
#endif
	) {
		*(uint32_t *)buff = (uint32_t) cpu_to_be32(0x1);

		return sizeof(uint32_t);
	} else
		return 0;
