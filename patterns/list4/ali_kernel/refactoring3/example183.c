switch (cmd) {
	case CYGETMON:
		if (copy_to_user(argp, &info->mon, sizeof(info->mon))) {
			ret_val = -EFAULT;
			break;
		}
		memset(&info->mon, 0, sizeof(info->mon));
		break;
	case CYGETTHRESH:
		ret_val = get_threshold(info, argp);
		break;
	case CYSETTHRESH:
		ret_val = set_threshold(info, arg);
		break;
	case CYGETDEFTHRESH:
		ret_val = put_user(info->default_threshold,
				(unsigned long __user *)argp);
		break;
	case CYSETDEFTHRESH:
		info->default_threshold = arg & 0x0f;
		break;
	case CYGETTIMEOUT:
		ret_val = get_timeout(info, argp);
		break;
	case CYSETTIMEOUT:
		ret_val = set_timeout(info, arg);
		break;
	case CYGETDEFTIMEOUT:
		ret_val = put_user(info->default_timeout,
				(unsigned long __user *)argp);
		break;
	case CYSETDEFTIMEOUT:
		info->default_timeout = arg & 0xff;
		break;
	case CYSETRFLOW:
		info->rflow = (int)arg;
		break;
	case CYGETRFLOW:
		ret_val = info->rflow;
		break;
	case CYSETRTSDTR_INV:
		info->rtsdtr_inv = (int)arg;
		break;
	case CYGETRTSDTR_INV:
		ret_val = info->rtsdtr_inv;
		break;
	case CYGETCD1400VER:
		ret_val = info->chip_rev;
		break;
#ifndef CONFIG_CYZ_INTR
	case CYZSETPOLLCYCLE:
		cyz_polling_cycle = (arg * HZ) / 1000;
		break;
	case CYZGETPOLLCYCLE:
		ret_val = (cyz_polling_cycle * 1000) / HZ;
		break;
#endif				/* CONFIG_CYZ_INTR */
	case CYSETWAIT:
		info->port.closing_wait = (unsigned short)arg * HZ / 100;
		break;
	case CYGETWAIT:
		ret_val = info->port.closing_wait / (HZ / 100);
		break;
	case TIOCGSERIAL:
		ret_val = cy_get_serial_info(info, argp);
		break;
	case TIOCSSERIAL:
		ret_val = cy_set_serial_info(info, tty, argp);
		break;
	case TIOCSERGETLSR:	/* Get line status register */
		ret_val = get_lsr_info(info, argp);
		break;
		/*
		 * Wait for any of the 4 modem inputs (DCD,RI,DSR,CTS) to change
		 * - mask passed in arg for lines of interest
		 *   (use |'ed TIOCM_RNG/DSR/CD/CTS for masking)
		 * Caller should use TIOCGICOUNT to see which one it was
		 */
	case TIOCMIWAIT:
		spin_lock_irqsave(&info->card->card_lock, flags);
		/* note the counters on entry */
		cnow = info->icount;
		spin_unlock_irqrestore(&info->card->card_lock, flags);
		ret_val = wait_event_interruptible(info->port.delta_msr_wait,
				cy_cflags_changed(info, arg, &cnow));
		break;

		/*
		 * Get counter of input serial line interrupts (DCD,RI,DSR,CTS)
		 * Return: write counters to the user passed counter struct
		 * NB: both 1->0 and 0->1 transitions are counted except for
		 *     RI where only 0->1 is counted.
		 */
	case TIOCGICOUNT: {
		struct serial_icounter_struct sic = { };

		spin_lock_irqsave(&info->card->card_lock, flags);
		cnow = info->icount;
		spin_unlock_irqrestore(&info->card->card_lock, flags);

		sic.cts = cnow.cts;
		sic.dsr = cnow.dsr;
		sic.rng = cnow.rng;
		sic.dcd = cnow.dcd;
		sic.rx = cnow.rx;
		sic.tx = cnow.tx;
		sic.frame = cnow.frame;
		sic.overrun = cnow.overrun;
		sic.parity = cnow.parity;
		sic.brk = cnow.brk;
		sic.buf_overrun = cnow.buf_overrun;

		if (copy_to_user(argp, &sic, sizeof(sic)))
			ret_val = -EFAULT;
		break;
	}
	default:
		ret_val = -ENOIOCTLCMD;
	}
