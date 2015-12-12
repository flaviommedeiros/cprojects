switch (cmd) {
#ifdef TIOCGETP
	case TIOCGETP:
		return get_sgttyb(real_tty, (struct sgttyb __user *) arg);
	case TIOCSETP:
	case TIOCSETN:
		return set_sgttyb(real_tty, (struct sgttyb __user *) arg);
#endif
#ifdef TIOCGETC
	case TIOCGETC:
		return get_tchars(real_tty, p);
	case TIOCSETC:
		return set_tchars(real_tty, p);
#endif
#ifdef TIOCGLTC
	case TIOCGLTC:
		return get_ltchars(real_tty, p);
	case TIOCSLTC:
		return set_ltchars(real_tty, p);
#endif
	case TCSETSF:
		return set_termios(real_tty, p,  TERMIOS_FLUSH | TERMIOS_WAIT | TERMIOS_OLD);
	case TCSETSW:
		return set_termios(real_tty, p, TERMIOS_WAIT | TERMIOS_OLD);
	case TCSETS:
		return set_termios(real_tty, p, TERMIOS_OLD);
#ifndef TCGETS2
	case TCGETS:
		copy_termios(real_tty, &kterm);
		if (kernel_termios_to_user_termios((struct termios __user *)arg, &kterm))
			ret = -EFAULT;
		return ret;
#else
	case TCGETS:
		copy_termios(real_tty, &kterm);
		if (kernel_termios_to_user_termios_1((struct termios __user *)arg, &kterm))
			ret = -EFAULT;
		return ret;
	case TCGETS2:
		copy_termios(real_tty, &kterm);
		if (kernel_termios_to_user_termios((struct termios2 __user *)arg, &kterm))
			ret = -EFAULT;
		return ret;
	case TCSETSF2:
		return set_termios(real_tty, p,  TERMIOS_FLUSH | TERMIOS_WAIT);
	case TCSETSW2:
		return set_termios(real_tty, p, TERMIOS_WAIT);
	case TCSETS2:
		return set_termios(real_tty, p, 0);
#endif
	case TCGETA:
		return get_termio(real_tty, p);
	case TCSETAF:
		return set_termios(real_tty, p, TERMIOS_FLUSH | TERMIOS_WAIT | TERMIOS_TERMIO);
	case TCSETAW:
		return set_termios(real_tty, p, TERMIOS_WAIT | TERMIOS_TERMIO);
	case TCSETA:
		return set_termios(real_tty, p, TERMIOS_TERMIO);
#ifndef TCGETS2
	case TIOCGLCKTRMIOS:
		copy_termios_locked(real_tty, &kterm);
		if (kernel_termios_to_user_termios((struct termios __user *)arg, &kterm))
			ret = -EFAULT;
		return ret;
	case TIOCSLCKTRMIOS:
		if (!capable(CAP_SYS_ADMIN))
			return -EPERM;
		copy_termios_locked(real_tty, &kterm);
		if (user_termios_to_kernel_termios(&kterm,
					       (struct termios __user *) arg))
			return -EFAULT;
		mutex_lock(&real_tty->termios_mutex);
		real_tty->termios_locked = kterm;
		mutex_unlock(&real_tty->termios_mutex);
		return 0;
#else
	case TIOCGLCKTRMIOS:
		copy_termios_locked(real_tty, &kterm);
		if (kernel_termios_to_user_termios_1((struct termios __user *)arg, &kterm))
			ret = -EFAULT;
		return ret;
	case TIOCSLCKTRMIOS:
		if (!capable(CAP_SYS_ADMIN))
			return -EPERM;
		copy_termios_locked(real_tty, &kterm);
		if (user_termios_to_kernel_termios_1(&kterm,
					       (struct termios __user *) arg))
			return -EFAULT;
		mutex_lock(&real_tty->termios_mutex);
		real_tty->termios_locked = kterm;
		mutex_unlock(&real_tty->termios_mutex);
		return ret;
#endif
#ifdef TCGETX
	case TCGETX: {
		struct termiox ktermx;
		if (real_tty->termiox == NULL)
			return -EINVAL;
		mutex_lock(&real_tty->termios_mutex);
		memcpy(&ktermx, real_tty->termiox, sizeof(struct termiox));
		mutex_unlock(&real_tty->termios_mutex);
		if (copy_to_user(p, &ktermx, sizeof(struct termiox)))
			ret = -EFAULT;
		return ret;
	}
	case TCSETX:
		return set_termiox(real_tty, p, 0);
	case TCSETXW:
		return set_termiox(real_tty, p, TERMIOS_WAIT);
	case TCSETXF:
		return set_termiox(real_tty, p, TERMIOS_FLUSH);
#endif		
	case TIOCGSOFTCAR:
		copy_termios(real_tty, &kterm);
		ret = put_user((kterm.c_cflag & CLOCAL) ? 1 : 0,
						(int __user *)arg);
		return ret;
	case TIOCSSOFTCAR:
		if (get_user(arg, (unsigned int __user *) arg))
			return -EFAULT;
		return tty_change_softcar(real_tty, arg);
	default:
		return -ENOIOCTLCMD;
	}
