switch (cmd) {
#ifdef RTC_SET_CHARGE
	case RTC_SET_CHARGE:
	{
		int tcs_val;

		if (copy_from_user(&tcs_val, (int __user *)arg, sizeof(int)))
			return -EFAULT;

		ds1302_writebyte(RTC_ADDR_TCR, (0xa0 | tcs_val * 0xf));
		return 0;
	}
#endif
	}
