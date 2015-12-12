if (
#ifdef SUPPORT_RMT
		    rmtioctl(arfd, MTIOCTOP, &mb)
#else
		    ioctl(arfd, MTIOCTOP, &mb)
#endif /* SUPPORT_RMT */
		    < 0) {
			syswarn(1, errno, "Unable to backspace tape %ld blocks.",
			    (long) mb.mt_count);
			lstrval = -1;
			return -1;
		}
