#ifdef USE_TTY_GROUP
if (fchmod(fd, sb.st_mode | S_IWGRP) < 0)
#else
		if (fchmod(fd, sb.st_mode | S_IWGRP | S_IWOTH) < 0)
#endif
			err(MESG_EXIT_FAILURE, _("change %s mode failed"), tty);
