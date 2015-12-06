#ifndef WIN32
if (ret > 0)
#endif
			// Relies on serial timeout for Windows
			ret = read(fd, buf, AVALON_FTDI_READSIZE);
