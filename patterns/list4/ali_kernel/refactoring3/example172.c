switch ( cmd ) {
		struct timeval par_timeout;
		long to_jiffies;

		case LPTIME:
			LP_TIME(minor) = arg * HZ/100;
			break;
		case LPCHAR:
			LP_CHAR(minor) = arg;
			break;
		case LPABORT:
			if (arg)
				LP_F(minor) |= LP_ABORT;
			else
				LP_F(minor) &= ~LP_ABORT;
			break;
		case LPABORTOPEN:
			if (arg)
				LP_F(minor) |= LP_ABORTOPEN;
			else
				LP_F(minor) &= ~LP_ABORTOPEN;
			break;
		case LPCAREFUL:
			if (arg)
				LP_F(minor) |= LP_CAREFUL;
			else
				LP_F(minor) &= ~LP_CAREFUL;
			break;
		case LPWAIT:
			LP_WAIT(minor) = arg;
			break;
		case LPSETIRQ: 
			return -EINVAL;
			break;
		case LPGETIRQ:
			if (copy_to_user(argp, &LP_IRQ(minor),
					sizeof(int)))
				return -EFAULT;
			break;
		case LPGETSTATUS:
			lp_claim_parport_or_block (&lp_table[minor]);
			status = r_str(minor);
			lp_release_parport (&lp_table[minor]);

			if (copy_to_user(argp, &status, sizeof(int)))
				return -EFAULT;
			break;
		case LPRESET:
			lp_reset(minor);
			break;
#ifdef LP_STATS
		case LPGETSTATS:
			if (copy_to_user(argp, &LP_STAT(minor),
					sizeof(struct lp_stats)))
				return -EFAULT;
			if (capable(CAP_SYS_ADMIN))
				memset(&LP_STAT(minor), 0,
						sizeof(struct lp_stats));
			break;
#endif
 		case LPGETFLAGS:
 			status = LP_F(minor);
			if (copy_to_user(argp, &status, sizeof(int)))
				return -EFAULT;
			break;

		case LPSETTIMEOUT:
			if (copy_from_user (&par_timeout, argp,
					    sizeof (struct timeval))) {
				return -EFAULT;
			}
			/* Convert to jiffies, place in lp_table */
			if ((par_timeout.tv_sec < 0) ||
			    (par_timeout.tv_usec < 0)) {
				return -EINVAL;
			}
			to_jiffies = DIV_ROUND_UP(par_timeout.tv_usec, 1000000/HZ);
			to_jiffies += par_timeout.tv_sec * (long) HZ;
			if (to_jiffies <= 0) {
				return -EINVAL;
			}
			lp_table[minor].timeout = to_jiffies;
			break;

		default:
			retval = -EINVAL;
	}
