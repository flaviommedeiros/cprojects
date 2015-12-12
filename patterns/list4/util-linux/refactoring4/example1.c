#if defined(__FreeBSD_kernel__)
if (ioctl(STDIN_FILENO, KDGKBMODE, &op->kbmode) == 0)
#else
	if (ioctl(STDIN_FILENO, TIOCMGET, &serial) < 0 && (errno == EINVAL))
#endif
	{
		op->flags |= F_VCONSOLE;
		if (!op->term)
			op->term = DEFAULT_VCTERM;
	} else {
#ifdef K_RAW
		op->kbmode = K_RAW;
#endif
		if (!op->term)
			op->term = DEFAULT_STERM;
	}
