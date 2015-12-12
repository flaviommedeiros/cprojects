if (tm->tm_hour < 0 || tm->tm_min < 0 || tm->tm_min > MINS_PER_HOUR - 1 ||
		tm->tm_sec < 0 || tm->tm_sec > SECS_PER_MINUTE ||
		tm->tm_hour > HOURS_PER_DAY ||
	/* test for > 24:00:00 */
		(tm->tm_hour == HOURS_PER_DAY &&
		 (tm->tm_min > 0 || tm->tm_sec > 0 || *fsec > 0)) ||
#ifdef HAVE_INT64_TIMESTAMP
		*fsec < INT64CONST(0) || *fsec > USECS_PER_SEC
#else
		*fsec < 0 || *fsec > 1
#endif
		)
		return DTERR_FIELD_OVERFLOW;
