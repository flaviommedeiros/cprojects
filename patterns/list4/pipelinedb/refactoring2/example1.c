#ifndef WIN32
if (!aborting)
#endif
			exit_horribly(modulename,
						"could not write to the communication channel: %s\n",
						  strerror(errno));
