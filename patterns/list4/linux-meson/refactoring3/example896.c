switch (cmd) {

	/*
	 * Here are all the standard ioctl's that we MUST implement
	 */

	case TCSBRK:
		/*
		 * TCSBRK is SVID version: non-zero arg --> no break
		 * this behaviour is exploited by tcdrain().
		 *
		 * According to POSIX.1 spec (7.2.2.1.2) breaks should be
		 * between 0.25 and 0.5 seconds
		 */

		rc = tty_check_change(tty);
		if (rc)
			return rc;
		tty_wait_until_sent(tty, 0);

		if (!arg)
			rc = dgrp_send_break(ch, 250); /* 1/4 second */

		if (dgrp_tty_chars_in_buffer(tty) != 0)
			return -EINTR;

		return 0;

	case TCSBRKP:
		/* support for POSIX tcsendbreak()
		 *
		 * According to POSIX.1 spec (7.2.2.1.2) breaks should be
		 * between 0.25 and 0.5 seconds so we'll ask for something
		 * in the middle: 0.375 seconds.
		 */
		rc = tty_check_change(tty);
		if (rc)
			return rc;
		tty_wait_until_sent(tty, 0);

		rc = dgrp_send_break(ch, arg ? arg*250 : 250);

		if (dgrp_tty_chars_in_buffer(tty) != 0)
			return -EINTR;
		return 0;

	case TIOCSBRK:
		rc = tty_check_change(tty);
		if (rc)
			return rc;
		tty_wait_until_sent(tty, 0);

		/*
		 * RealPort doesn't support turning on a break unconditionally.
		 * The RealPort device will stop sending a break automatically
		 * after the specified time value that we send in.
		 */
		rc = dgrp_send_break(ch, 250); /* 1/4 second */

		if (dgrp_tty_chars_in_buffer(tty) != 0)
			return -EINTR;
		return 0;

	case TIOCCBRK:
		/*
		 * RealPort doesn't support turning off a break unconditionally.
		 * The RealPort device will stop sending a break automatically
		 * after the specified time value that was sent when turning on
		 * the break.
		 */
		return 0;

	case TIOCMGET:
		rc = access_ok(VERIFY_WRITE, (void __user *) arg,
				 sizeof(unsigned int));
		if (rc == 0)
			return -EFAULT;
		return get_modem_info(ch, (unsigned int *) arg);

	case TIOCMBIS:
	case TIOCMBIC:
	case TIOCMSET:
		return set_modem_info(ch, cmd, (unsigned int *) arg);

	/*
	 * Here are any additional ioctl's that we want to implement
	 */

	case TCFLSH:
		/*
		 * The linux tty driver doesn't have a flush
		 * input routine for the driver, assuming all backed
		 * up data is in the line disc. buffers.  However,
		 * we all know that's not the case.  Here, we
		 * act on the ioctl, but then lie and say we didn't
		 * so the line discipline will process the flush
		 * also.
		 */
		rc = tty_check_change(tty);
		if (rc)
			return rc;

		switch (arg) {
		case TCIFLUSH:
		case TCIOFLUSH:
			/* only flush input if this is the only open unit */
			if (!IS_PRINT(MINOR(tty_devnum(tty)))) {
				ch->ch_rout = ch->ch_rin;
				ch->ch_send |= RR_RX_FLUSH;
				(ch->ch_nd)->nd_tx_work = 1;
				(ch->ch_nd)->nd_tx_ready = 1;
				wake_up_interruptible(&(ch->ch_nd)->nd_tx_waitq);
			}
			if (arg == TCIFLUSH)
				break;

		case TCOFLUSH: /* flush output, or the receive buffer */
			/*
			 * This is handled in the tty_ioctl.c code
			 * calling tty_flush_buffer
			 */
			break;

		default:
			/* POSIX.1 says return EINVAL if we got a bad arg */
			return -EINVAL;
		}
		/* pretend we didn't recognize this IOCTL */
		return -ENOIOCTLCMD;

#ifdef TIOCGETP
	case TIOCGETP:
#endif
	/*****************************************
	Linux		HPUX		Function
	TCSETA		TCSETA		- set the termios
	TCSETAF		TCSETAF		- wait for drain first, then set termios
	TCSETAW		TCSETAW		- wait for drain, flush the input queue, then set termios
	- looking at the tty_ioctl code, these command all call our
	tty_set_termios at the driver's end, when a TCSETA* is sent,
	it is expecting the tty to have a termio structure,
	NOT a termios structure.  These two structures differ in size
	and the tty_ioctl code does a conversion before processing them both.
	- we should treat the TCSETAW TCSETAF ioctls the same, and let
	the tty_ioctl code do the conversion stuff.

	TCSETS
	TCSETSF		(none)
	TCSETSW
	- the associated tty structure has a termios structure.
	*****************************************/

	case TCGETS:
	case TCGETA:
		return -ENOIOCTLCMD;

	case TCSETAW:
	case TCSETAF:
	case TCSETSF:
	case TCSETSW:
		/*
		 * The linux tty driver doesn't have a flush
		 * input routine for the driver, assuming all backed
		 * up data is in the line disc. buffers.  However,
		 * we all know that's not the case.  Here, we
		 * act on the ioctl, but then lie and say we didn't
		 * so the line discipline will process the flush
		 * also.
		 */

		/*
		 * Also, now that we have TXPrint, we have to check
		 * if this is the TXPrint device and the terminal
		 * device is open. If so, do NOT run check_change,
		 * as the terminal device is ALWAYS the parent.
		 */
		if (!IS_PRINT(MINOR(tty_devnum(tty))) ||
		    !ch->ch_tun.un_open_count) {
			rc = tty_check_change(tty);
			if (rc)
				return rc;
		}

		/* wait for all the characters in tbuf to drain */
		tty_wait_until_sent(tty, 0);

		if ((cmd == TCSETSF) || (cmd == TCSETAF)) {
			/* flush the contents of the rbuf queue */
			/* TODO:  check if this is print device? */
			ch->ch_send |= RR_RX_FLUSH;
			(ch->ch_nd)->nd_tx_ready = 1;
			(ch->ch_nd)->nd_tx_work = 1;
			wake_up_interruptible(&(ch->ch_nd)->nd_tx_waitq);
			/* do we need to do this?  just to be safe! */
			ch->ch_rout = ch->ch_rin;
		}

		/* pretend we didn't recognize this */
		return -ENOIOCTLCMD;

	case TCXONC:
		/*
		 * The Linux Line Discipline (LD) would do this for us if we
		 * let it, but we have the special firmware options to do this
		 * the "right way" regardless of hardware or software flow
		 * control so we'll do it outselves instead of letting the LD
		 * do it.
		 */
		rc = tty_check_change(tty);
		if (rc)
			return rc;

		switch (arg) {
		case TCOON:
			dgrp_tty_start(tty);
			return 0;
		case TCOOFF:
			dgrp_tty_stop(tty);
			return 0;
		case TCION:
			dgrp_tty_input_start(tty);
			return 0;
		case TCIOFF:
			dgrp_tty_input_stop(tty);
			return 0;
		default:
			return -EINVAL;
		}

	case DIGI_GETA:
		/* get information for ditty */
		if (copy_to_user((struct digi_struct __user *) arg,
				 &ch->ch_digi, sizeof(struct digi_struct)))
			return -EFAULT;
		break;

	case DIGI_SETAW:
	case DIGI_SETAF:
		/* wait for all the characters in tbuf to drain */
		tty_wait_until_sent(tty, 0);

		if (cmd == DIGI_SETAF) {
			/* flush the contents of the rbuf queue */
			/* send down a packet with RR_RX_FLUSH set */
			ch->ch_send |= RR_RX_FLUSH;
			(ch->ch_nd)->nd_tx_ready = 1;
			(ch->ch_nd)->nd_tx_work = 1;
			wake_up_interruptible(&(ch->ch_nd)->nd_tx_waitq);
			/* do we need to do this?  just to be safe! */
			ch->ch_rout = ch->ch_rin;
		}

		/* pretend we didn't recognize this */

	case DIGI_SETA:
		return dgrp_tty_digiseta(tty, (struct digi_struct *) arg);

	case DIGI_SEDELAY:
		return dgrp_tty_digisetedelay(tty, (int *) arg);

	case DIGI_GEDELAY:
		return dgrp_tty_digigetedelay(tty, (int *) arg);

	case DIGI_GETFLOW:
	case DIGI_GETAFLOW:
		if (cmd == (DIGI_GETFLOW)) {
			dflow.startc = tty->termios.c_cc[VSTART];
			dflow.stopc = tty->termios.c_cc[VSTOP];
		} else {
			dflow.startc = ch->ch_xxon;
			dflow.stopc = ch->ch_xxoff;
		}

		if (copy_to_user((char __user *)arg, &dflow, sizeof(dflow)))
			return -EFAULT;
		break;

	case DIGI_SETFLOW:
	case DIGI_SETAFLOW:

		if (copy_from_user(&dflow, (char __user *)arg, sizeof(dflow)))
			return -EFAULT;

		if (cmd == (DIGI_SETFLOW)) {
			tty->termios.c_cc[VSTART] = dflow.startc;
			tty->termios.c_cc[VSTOP] = dflow.stopc;
		} else {
			ch->ch_xxon = dflow.startc;
			ch->ch_xxoff = dflow.stopc;
		}
		break;

	case DIGI_GETCUSTOMBAUD:
		if (put_user(ch->ch_custom_speed, (unsigned int __user *) arg))
			return -EFAULT;
		break;

	case DIGI_SETCUSTOMBAUD:
	{
		int new_rate;

		if (get_user(new_rate, (unsigned int __user *) arg))
			return -EFAULT;
		dgrp_set_custom_speed(ch, new_rate);

		break;
	}

	default:
		return -ENOIOCTLCMD;
	}
