if (strftime(buf, sizeof(buf),
#ifndef WIN32
				 "%Y-%m-%d %H:%M:%S %Z",
#else
				 "%Y-%m-%d %H:%M:%S",
#endif
				 localtime(&tim)) != 0)
		ahprintf(AH, "-- %s %s\n\n", msg, buf);
