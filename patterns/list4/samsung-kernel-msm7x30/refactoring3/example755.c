switch(cmd) {
#ifdef TIOCGETP
	case TIOCGETP:
	case TIOCSETP:
	case TIOCSETN:
#endif
#ifdef TIOCGETC
	case TIOCGETC:
	case TIOCSETC:
#endif
#ifdef TIOCGLTC
	case TIOCGLTC:
	case TIOCSLTC:
#endif
	/* Note: these are out of date as we now have TCGETS2 etc but this
	   whole lot should probably go away */
	case TCGETS:
	case TCSETSF:
	case TCSETSW:
	case TCSETS:
	case TCGETA:
	case TCSETAF:
	case TCSETAW:
	case TCSETA:
	case TCXONC:
	case TCFLSH:
	case TIOCOUTQ:
	case TIOCINQ:
	case TIOCGLCKTRMIOS:
	case TIOCSLCKTRMIOS:
	case TIOCPKT:
	case TIOCGSOFTCAR:
	case TIOCSSOFTCAR:
		return -ENOIOCTLCMD;
#if 0
	case TCwhatever:
		/* do something */
		break;
#endif
	default:
		for (i = 0; i < ARRAY_SIZE(tty_ioctls); i++)
			if (cmd == tty_ioctls[i].cmd)
				break;
		if (i == ARRAY_SIZE(tty_ioctls)) {
			printk(KERN_ERR "%s: %s: unknown ioctl: 0x%x\n",
			       __func__, tty->name, cmd);
		}
		ret = -ENOIOCTLCMD;
		break;
	}
