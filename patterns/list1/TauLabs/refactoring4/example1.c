#if defined(AQ32)
if ((good_runs > REQUIRED_GOOD_CYCLES) && !external_mag_fail)
		#else
		if (good_runs > REQUIRED_GOOD_CYCLES)
		#endif
			AlarmsClear(SYSTEMALARMS_ALARM_SENSORS);
		else
			good_runs++;
