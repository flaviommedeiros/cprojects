switch (cmd) {
#ifdef RTC_SET_CHARGE
	case RTC_SET_CHARGE:
	{
		int val;

		if (copy_from_user(&val, (int __user *)arg, sizeof(int)))
			return -EFAULT;

		return regmap_write(priv->map, DS1343_TRICKLE_REG, val);
	}
	break;
#endif
	}
