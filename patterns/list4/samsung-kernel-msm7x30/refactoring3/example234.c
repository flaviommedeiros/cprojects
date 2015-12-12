switch (cmd) {
	case CM_IOCGSTATUS:
		DEBUGP(4, dev, " ... in CM_IOCGSTATUS\n");
		{
			int status;

			/* clear other bits, but leave inserted & powered as
			 * they are */
			status = dev->flags0 & 3;
			if (test_bit(IS_ATR_PRESENT, &dev->flags))
				status |= CM_ATR_PRESENT;
			if (test_bit(IS_ATR_VALID, &dev->flags))
				status |= CM_ATR_VALID;
			if (test_bit(IS_CMM_ABSENT, &dev->flags))
				status |= CM_NO_READER;
			if (test_bit(IS_BAD_CARD, &dev->flags))
				status |= CM_BAD_CARD;
			if (copy_to_user(argp, &status, sizeof(int)))
				rc = -EFAULT;
		}
		break;
	case CM_IOCGATR:
		DEBUGP(4, dev, "... in CM_IOCGATR\n");
		{
			struct atreq __user *atreq = argp;
			int tmp;
			/* allow nonblocking io and being interrupted */
			if (wait_event_interruptible
			    (dev->atrq,
			     ((filp->f_flags & O_NONBLOCK)
			      || (test_bit(IS_ATR_PRESENT, (void *)&dev->flags)
				  != 0)))) {
				if (filp->f_flags & O_NONBLOCK)
					rc = -EAGAIN;
				else
					rc = -ERESTARTSYS;
				break;
			}

			rc = -EFAULT;
			if (test_bit(IS_ATR_VALID, &dev->flags) == 0) {
				tmp = -1;
				if (copy_to_user(&(atreq->atr_len), &tmp,
						 sizeof(int)))
					break;
			} else {
				if (copy_to_user(atreq->atr, dev->atr,
						 dev->atr_len))
					break;

				tmp = dev->atr_len;
				if (copy_to_user(&(atreq->atr_len), &tmp, sizeof(int)))
					break;
			}
			rc = 0;
			break;
		}
	case CM_IOCARDOFF:

#ifdef CM4000_DEBUG
		DEBUGP(4, dev, "... in CM_IOCARDOFF\n");
		if (dev->flags0 & 0x01) {
			DEBUGP(4, dev, "    Card inserted\n");
		} else {
			DEBUGP(2, dev, "    No card inserted\n");
		}
		if (dev->flags0 & 0x02) {
			DEBUGP(4, dev, "    Card powered\n");
		} else {
			DEBUGP(2, dev, "    Card not powered\n");
		}
#endif

		/* is a card inserted and powered? */
		if ((dev->flags0 & 0x01) && (dev->flags0 & 0x02)) {

			/* get IO lock */
			if (wait_event_interruptible
			    (dev->ioq,
			     ((filp->f_flags & O_NONBLOCK)
			      || (test_and_set_bit(LOCK_IO, (void *)&dev->flags)
				  == 0)))) {
				if (filp->f_flags & O_NONBLOCK)
					rc = -EAGAIN;
				else
					rc = -ERESTARTSYS;
				break;
			}
			/* Set Flags0 = 0x42 */
			DEBUGP(4, dev, "Set Flags0=0x42 \n");
			xoutb(0x42, REG_FLAGS0(iobase));
			clear_bit(IS_ATR_PRESENT, &dev->flags);
			clear_bit(IS_ATR_VALID, &dev->flags);
			dev->mstate = M_CARDOFF;
			clear_bit(LOCK_IO, &dev->flags);
			if (wait_event_interruptible
			    (dev->atrq,
			     ((filp->f_flags & O_NONBLOCK)
			      || (test_bit(IS_ATR_VALID, (void *)&dev->flags) !=
				  0)))) {
				if (filp->f_flags & O_NONBLOCK)
					rc = -EAGAIN;
				else
					rc = -ERESTARTSYS;
				break;
			}
		}
		/* release lock */
		clear_bit(LOCK_IO, &dev->flags);
		wake_up_interruptible(&dev->ioq);

		rc = 0;
		break;
	case CM_IOCSPTS:
		{
			struct ptsreq krnptsreq;

			if (copy_from_user(&krnptsreq, argp,
					   sizeof(struct ptsreq))) {
				rc = -EFAULT;
				break;
			}

			rc = 0;
			DEBUGP(4, dev, "... in CM_IOCSPTS\n");
			/* wait for ATR to get valid */
			if (wait_event_interruptible
			    (dev->atrq,
			     ((filp->f_flags & O_NONBLOCK)
			      || (test_bit(IS_ATR_PRESENT, (void *)&dev->flags)
				  != 0)))) {
				if (filp->f_flags & O_NONBLOCK)
					rc = -EAGAIN;
				else
					rc = -ERESTARTSYS;
				break;
			}
			/* get IO lock */
			if (wait_event_interruptible
			    (dev->ioq,
			     ((filp->f_flags & O_NONBLOCK)
			      || (test_and_set_bit(LOCK_IO, (void *)&dev->flags)
				  == 0)))) {
				if (filp->f_flags & O_NONBLOCK)
					rc = -EAGAIN;
				else
					rc = -ERESTARTSYS;
				break;
			}

			if ((rc = set_protocol(dev, &krnptsreq)) != 0) {
				/* auto power_on again */
				dev->mstate = M_FETCH_ATR;
				clear_bit(IS_ATR_VALID, &dev->flags);
			}
			/* release lock */
			clear_bit(LOCK_IO, &dev->flags);
			wake_up_interruptible(&dev->ioq);

		}
		break;
#ifdef CM4000_DEBUG
	case CM_IOSDBGLVL:
		rc = -ENOTTY;
		break;
#endif
	default:
		DEBUGP(4, dev, "... in default (unknown IOCTL code)\n");
		rc = -ENOTTY;
	}
