switch (cmd) {
	case LIRC_GET_FEATURES:
	case LIRC_GET_SEND_MODE:
	case LIRC_GET_REC_MODE:
		retval = put_user(value, (__u32 *) arg);
		break;

	case LIRC_SET_SEND_MODE:
	case LIRC_SET_REC_MODE:
		retval = get_user(value, (__u32 *) arg);
		break;
#ifdef LIRC_ON_SA1100
	case LIRC_SET_SEND_DUTY_CYCLE:
		retval = get_user(value, (__u32 *) arg);
		if (retval)
			return retval;
		if (value <= 0 || value > 100)
			return -EINVAL;
		/* (value/100)*(1000000/freq) */
		duty_cycle = value;
		pulse_width = (unsigned long) duty_cycle*10000/freq;
		space_width = (unsigned long) 1000000L/freq-pulse_width;
		if (pulse_width >= LIRC_ON_SA1100_TRANSMITTER_LATENCY)
			pulse_width -= LIRC_ON_SA1100_TRANSMITTER_LATENCY;
		if (space_width >= LIRC_ON_SA1100_TRANSMITTER_LATENCY)
			space_width -= LIRC_ON_SA1100_TRANSMITTER_LATENCY;
		break;
	case LIRC_SET_SEND_CARRIER:
		retval = get_user(value, (__u32 *) arg);
		if (retval)
			return retval;
		if (value > 500000 || value < 20000)
			return -EINVAL;
		freq = value;
		pulse_width = (unsigned long) duty_cycle*10000/freq;
		space_width = (unsigned long) 1000000L/freq-pulse_width;
		if (pulse_width >= LIRC_ON_SA1100_TRANSMITTER_LATENCY)
			pulse_width -= LIRC_ON_SA1100_TRANSMITTER_LATENCY;
		if (space_width >= LIRC_ON_SA1100_TRANSMITTER_LATENCY)
			space_width -= LIRC_ON_SA1100_TRANSMITTER_LATENCY;
		break;
#endif
	default:
		retval = -ENOIOCTLCMD;

	}
