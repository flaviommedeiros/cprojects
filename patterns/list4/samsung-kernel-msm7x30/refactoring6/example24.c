if ((rtc_args->proc == TIMEREMOTE_PROCEEDURE_GET_JULIAN)
#ifdef CONFIG_RTC_SECURE_TIME_SUPPORT
	|| (rtc_args->proc == TIMEREMOTE_PROCEEDURE_GET_SECURE_JULIAN)
#endif
	)  {
		struct timeremote_get_julian_rep {
			uint32_t opt_arg;
			struct rpc_time_julian time;
		};
		struct timeremote_get_julian_rep *result = buff;

		if (be32_to_cpu(result->opt_arg) != 0x1)
			return -ENODATA;

		rtc_args->tm->tm_year = be32_to_cpu(result->time.year);
		rtc_args->tm->tm_mon = be32_to_cpu(result->time.month);
		rtc_args->tm->tm_mday = be32_to_cpu(result->time.day);
		rtc_args->tm->tm_hour = be32_to_cpu(result->time.hour);
		rtc_args->tm->tm_min = be32_to_cpu(result->time.minute);
		rtc_args->tm->tm_sec = be32_to_cpu(result->time.second);
		rtc_args->tm->tm_wday = be32_to_cpu(result->time.day_of_week);

		pr_debug("%s: %.2u/%.2u/%.4u %.2u:%.2u:%.2u (%.2u)\n",
			__func__, rtc_args->tm->tm_mon, rtc_args->tm->tm_mday,
			rtc_args->tm->tm_year, rtc_args->tm->tm_hour,
			rtc_args->tm->tm_min, rtc_args->tm->tm_sec,
			rtc_args->tm->tm_wday);

		/* RTC layer expects years to start at 1900 */
		rtc_args->tm->tm_year -= 1900;
		/* RTC layer expects mons to be 0 based */
		rtc_args->tm->tm_mon--;

		if (rtc_valid_tm(rtc_args->tm) < 0) {
			pr_err("%s: Retrieved data/time not valid\n", __func__);
			rtc_time_to_tm(0, rtc_args->tm);
		}

		/*
		 * Check if the time received is > 01-19-2038, to prevent
		 * overflow. In such a case, return the EPOCH time.
		 */
		if (rtc_check_overflow(rtc_args->tm) == true) {
			pr_err("Invalid time (year > 2038)\n");
			rtc_time_to_tm(0, rtc_args->tm);
		}

		return 0;
	} else
		return 0;
