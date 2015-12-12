#if defined(KDGKBMODE)
if (ioctl(fd, KDGKBMODE, &mode) < 0)
#endif
	{
		speed_t ispeed, ospeed;
		struct winsize ws;
		errno = 0;

		/* this is a modem line */
		con->flags |= CON_SERIAL;

		/* Flush input and output queues on modem lines */
		tcflush(fd, TCIOFLUSH);

		ispeed = cfgetispeed(tio);
		ospeed = cfgetospeed(tio);

		if (!ispeed) ispeed = TTYDEF_SPEED;
		if (!ospeed) ospeed = TTYDEF_SPEED;

		tio->c_cflag = CREAD | CS8 | HUPCL | (tio->c_cflag & CLOCAL);
		tio->c_iflag = 0;
		tio->c_lflag = 0;
		tio->c_oflag &= OPOST | ONLCR;

		cfsetispeed(tio, ispeed);
		cfsetospeed(tio, ospeed);

#ifdef HAVE_STRUCT_TERMIOS_C_LINE
		tio->c_line         = 0;
#endif
		tio->c_cc[VTIME]    = 0;
		tio->c_cc[VMIN]     = 1;

		if (ioctl(fd, TIOCGWINSZ, &ws) == 0) {
			int set = 0;
			if (ws.ws_row == 0) {
				ws.ws_row = 24;
				set++;
			}
			if (ws.ws_col == 0) {
				ws.ws_col = 80;
				set++;
			}
			if (set)
				ignore_result( ioctl(fd, TIOCSWINSZ, &ws) );
		}

		setlocale(LC_CTYPE, "POSIX");
		goto setattr;
	}
