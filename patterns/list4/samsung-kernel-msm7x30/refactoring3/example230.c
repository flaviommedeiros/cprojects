switch ( cmd ) {
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

		default:
			retval = -EINVAL;
	}
