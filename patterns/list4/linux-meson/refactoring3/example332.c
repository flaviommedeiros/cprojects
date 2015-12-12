switch (cmd) {
#ifdef RTC_IRQ
	case RTC_AIE_OFF:	/* Mask alarm int. enab. bit	*/
	{
		mask_rtc_irq_bit(RTC_AIE);
		return 0;
	}
	case RTC_AIE_ON:	/* Allow alarm interrupts.	*/
	{
		set_rtc_irq_bit(RTC_AIE);
		return 0;
	}
	case RTC_PIE_OFF:	/* Mask periodic int. enab. bit	*/
	{
		/* can be called from isr via rtc_control() */
		unsigned long flags;

		spin_lock_irqsave(&rtc_lock, flags);
		mask_rtc_irq_bit_locked(RTC_PIE);
		if (rtc_status & RTC_TIMER_ON) {
			rtc_status &= ~RTC_TIMER_ON;
			del_timer(&rtc_irq_timer);
		}
		spin_unlock_irqrestore(&rtc_lock, flags);

		return 0;
	}
	case RTC_PIE_ON:	/* Allow periodic ints		*/
	{
		/* can be called from isr via rtc_control() */
		unsigned long flags;

		/*
		 * We don't really want Joe User enabling more
		 * than 64Hz of interrupts on a multi-user machine.
		 */
		if (!kernel && (rtc_freq > rtc_max_user_freq) &&
						(!capable(CAP_SYS_RESOURCE)))
			return -EACCES;

		spin_lock_irqsave(&rtc_lock, flags);
		if (!(rtc_status & RTC_TIMER_ON)) {
			mod_timer(&rtc_irq_timer, jiffies + HZ/rtc_freq +
					2*HZ/100);
			rtc_status |= RTC_TIMER_ON;
		}
		set_rtc_irq_bit_locked(RTC_PIE);
		spin_unlock_irqrestore(&rtc_lock, flags);

		return 0;
	}
	case RTC_UIE_OFF:	/* Mask ints from RTC updates.	*/
	{
		mask_rtc_irq_bit(RTC_UIE);
		return 0;
	}
	case RTC_UIE_ON:	/* Allow ints for RTC updates.	*/
	{
		set_rtc_irq_bit(RTC_UIE);
		return 0;
	}
#endif
	case RTC_ALM_READ:	/* Read the present alarm time */
	{
		/*
		 * This returns a struct rtc_time. Reading >= 0xc0
		 * means "don't care" or "match all". Only the tm_hour,
		 * tm_min, and tm_sec values are filled in.
		 */
		memset(&wtime, 0, sizeof(struct rtc_time));
		get_rtc_alm_time(&wtime);
		break;
	}
	case RTC_ALM_SET:	/* Store a time into the alarm */
	{
		/*
		 * This expects a struct rtc_time. Writing 0xff means
		 * "don't care" or "match all". Only the tm_hour,
		 * tm_min and tm_sec are used.
		 */
		unsigned char hrs, min, sec;
		struct rtc_time alm_tm;

		if (copy_from_user(&alm_tm, (struct rtc_time __user *)arg,
				   sizeof(struct rtc_time)))
			return -EFAULT;

		hrs = alm_tm.tm_hour;
		min = alm_tm.tm_min;
		sec = alm_tm.tm_sec;

		spin_lock_irq(&rtc_lock);
		if (hpet_set_alarm_time(hrs, min, sec)) {
			/*
			 * Fallthru and set alarm time in CMOS too,
			 * so that we will get proper value in RTC_ALM_READ
			 */
		}
		if (!(CMOS_READ(RTC_CONTROL) & RTC_DM_BINARY) ||
							RTC_ALWAYS_BCD) {
			if (sec < 60)
				sec = bin2bcd(sec);
			else
				sec = 0xff;

			if (min < 60)
				min = bin2bcd(min);
			else
				min = 0xff;

			if (hrs < 24)
				hrs = bin2bcd(hrs);
			else
				hrs = 0xff;
		}
		CMOS_WRITE(hrs, RTC_HOURS_ALARM);
		CMOS_WRITE(min, RTC_MINUTES_ALARM);
		CMOS_WRITE(sec, RTC_SECONDS_ALARM);
		spin_unlock_irq(&rtc_lock);

		return 0;
	}
	case RTC_RD_TIME:	/* Read the time/date from RTC	*/
	{
		memset(&wtime, 0, sizeof(struct rtc_time));
		rtc_get_rtc_time(&wtime);
		break;
	}
	case RTC_SET_TIME:	/* Set the RTC */
	{
		struct rtc_time rtc_tm;
		unsigned char mon, day, hrs, min, sec, leap_yr;
		unsigned char save_control, save_freq_select;
		unsigned int yrs;
#ifdef CONFIG_MACH_DECSTATION
		unsigned int real_yrs;
#endif

		if (!capable(CAP_SYS_TIME))
			return -EACCES;

		if (copy_from_user(&rtc_tm, (struct rtc_time __user *)arg,
				   sizeof(struct rtc_time)))
			return -EFAULT;

		yrs = rtc_tm.tm_year + 1900;
		mon = rtc_tm.tm_mon + 1;   /* tm_mon starts at zero */
		day = rtc_tm.tm_mday;
		hrs = rtc_tm.tm_hour;
		min = rtc_tm.tm_min;
		sec = rtc_tm.tm_sec;

		if (yrs < 1970)
			return -EINVAL;

		leap_yr = ((!(yrs % 4) && (yrs % 100)) || !(yrs % 400));

		if ((mon > 12) || (day == 0))
			return -EINVAL;

		if (day > (days_in_mo[mon] + ((mon == 2) && leap_yr)))
			return -EINVAL;

		if ((hrs >= 24) || (min >= 60) || (sec >= 60))
			return -EINVAL;

		yrs -= epoch;
		if (yrs > 255)		/* They are unsigned */
			return -EINVAL;

		spin_lock_irq(&rtc_lock);
#ifdef CONFIG_MACH_DECSTATION
		real_yrs = yrs;
		yrs = 72;

		/*
		 * We want to keep the year set to 73 until March
		 * for non-leap years, so that Feb, 29th is handled
		 * correctly.
		 */
		if (!leap_yr && mon < 3) {
			real_yrs--;
			yrs = 73;
		}
#endif
		/* These limits and adjustments are independent of
		 * whether the chip is in binary mode or not.
		 */
		if (yrs > 169) {
			spin_unlock_irq(&rtc_lock);
			return -EINVAL;
		}
		if (yrs >= 100)
			yrs -= 100;

		if (!(CMOS_READ(RTC_CONTROL) & RTC_DM_BINARY)
		    || RTC_ALWAYS_BCD) {
			sec = bin2bcd(sec);
			min = bin2bcd(min);
			hrs = bin2bcd(hrs);
			day = bin2bcd(day);
			mon = bin2bcd(mon);
			yrs = bin2bcd(yrs);
		}

		save_control = CMOS_READ(RTC_CONTROL);
		CMOS_WRITE((save_control|RTC_SET), RTC_CONTROL);
		save_freq_select = CMOS_READ(RTC_FREQ_SELECT);
		CMOS_WRITE((save_freq_select|RTC_DIV_RESET2), RTC_FREQ_SELECT);

#ifdef CONFIG_MACH_DECSTATION
		CMOS_WRITE(real_yrs, RTC_DEC_YEAR);
#endif
		CMOS_WRITE(yrs, RTC_YEAR);
		CMOS_WRITE(mon, RTC_MONTH);
		CMOS_WRITE(day, RTC_DAY_OF_MONTH);
		CMOS_WRITE(hrs, RTC_HOURS);
		CMOS_WRITE(min, RTC_MINUTES);
		CMOS_WRITE(sec, RTC_SECONDS);

		CMOS_WRITE(save_control, RTC_CONTROL);
		CMOS_WRITE(save_freq_select, RTC_FREQ_SELECT);

		spin_unlock_irq(&rtc_lock);
		return 0;
	}
#ifdef RTC_IRQ
	case RTC_IRQP_READ:	/* Read the periodic IRQ rate.	*/
	{
		return put_user(rtc_freq, (unsigned long __user *)arg);
	}
	case RTC_IRQP_SET:	/* Set periodic IRQ rate.	*/
	{
		int tmp = 0;
		unsigned char val;
		/* can be called from isr via rtc_control() */
		unsigned long flags;

		/*
		 * The max we can do is 8192Hz.
		 */
		if ((arg < 2) || (arg > 8192))
			return -EINVAL;
		/*
		 * We don't really want Joe User generating more
		 * than 64Hz of interrupts on a multi-user machine.
		 */
		if (!kernel && (arg > rtc_max_user_freq) &&
					!capable(CAP_SYS_RESOURCE))
			return -EACCES;

		while (arg > (1<<tmp))
			tmp++;

		/*
		 * Check that the input was really a power of 2.
		 */
		if (arg != (1<<tmp))
			return -EINVAL;

		rtc_freq = arg;

		spin_lock_irqsave(&rtc_lock, flags);
		if (hpet_set_periodic_freq(arg)) {
			spin_unlock_irqrestore(&rtc_lock, flags);
			return 0;
		}

		val = CMOS_READ(RTC_FREQ_SELECT) & 0xf0;
		val |= (16 - tmp);
		CMOS_WRITE(val, RTC_FREQ_SELECT);
		spin_unlock_irqrestore(&rtc_lock, flags);
		return 0;
	}
#endif
	case RTC_EPOCH_READ:	/* Read the epoch.	*/
	{
		return put_user(epoch, (unsigned long __user *)arg);
	}
	case RTC_EPOCH_SET:	/* Set the epoch.	*/
	{
		/*
		 * There were no RTC clocks before 1900.
		 */
		if (arg < 1900)
			return -EINVAL;

		if (!capable(CAP_SYS_TIME))
			return -EACCES;

		epoch = arg;
		return 0;
	}
	default:
		return -ENOTTY;
	}
