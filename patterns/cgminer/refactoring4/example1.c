#ifndef USE_USBUTILS
if (cgpu)
#else
				if (cgpu && !cgpu->usbinfo.nodev)
#endif
					curses_print_devstatus(cgpu, i, count++);
