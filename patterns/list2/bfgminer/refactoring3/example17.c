switch (input) {
			case 'd': case 'D':
				if (cgpu->deven == DEV_DISABLED)
					msg = "Processor already disabled\n";
				else
				{
					cgpu->deven = DEV_DISABLED;
					msg = "Processor being disabled\n";
				}
				goto refresh;
			case 'e': case 'E':
				if (cgpu->deven == DEV_ENABLED)
					msg = "Processor already enabled\n";
				else
				{
					proc_enable(cgpu);
					msg = "Processor being enabled\n";
				}
				goto refresh;
			case 'i': case 'I':
				if (drv->identify_device && drv->identify_device(cgpu))
					msg = "Identify command sent\n";
				else
					goto key_default;
				goto refresh;
			case KEY_DOWN:
				if (selected_device >= total_devices - 1)
					break;
				++selected_device;
				goto devchange;
			case KEY_UP:
				if (selected_device <= 0)
					break;
				--selected_device;
				goto devchange;
			case KEY_NPAGE:
			{
				if (selected_device >= total_devices - 1)
					break;
				struct cgpu_info *mdev = devices[selected_device]->device;
				do {
					++selected_device;
				} while (devices[selected_device]->device == mdev && selected_device < total_devices - 1);
				goto devchange;
			}
			case KEY_PPAGE:
			{
				if (selected_device <= 0)
					break;
				struct cgpu_info *mdev = devices[selected_device]->device;
				do {
					--selected_device;
				} while (devices[selected_device]->device == mdev && selected_device > 0);
				goto devchange;
			}
			case '/':  case '?':  // find device
			{
				static char *pattern = NULL;
				char *newpattern = curses_input("Enter pattern");
				if (newpattern)
				{
					free(pattern);
					pattern = newpattern;
				}
				else
				if (!pattern)
					pattern = calloc(1, 1);
				int match = cgpu_search(pattern, selected_device + 1);
				if (match == -1)
				{
					msg = "Couldn't find device\n";
					goto refresh;
				}
				selected_device = match;
				goto devchange;
			}
			case '+':  case '=':  // add new device
			{
addnew:
				clear_logwin();
				_wlogprint(
					"Enter \"auto\", \"all\", or a serial port to probe for mining devices.\n"
					"Prefix by a driver name and colon to only probe a specific driver.\n"
					"For example: erupter:"
#ifdef WIN32
					"\\\\.\\COM40"
#elif defined(__APPLE__)
					"/dev/cu.SLAB_USBtoUART"
#else
					"/dev/ttyUSB39"
#endif
					"\n"
				);
				char *scanser = curses_input("Enter target");
				if (scan_serial(scanser))
				{
					selected_device = total_devices - 1;
					msg = "Device scan succeeded\n";
				}
				else
					msg = "No new devices found\n";
				goto devchange;
			}
			case 'Q': case 'q':
			case KEY_BREAK: case KEY_BACKSPACE: case KEY_CANCEL: case KEY_CLOSE: case KEY_EXIT:
			case '\x1b':  // ESC
			case KEY_ENTER:
			case '\r':  // Ctrl-M on Windows, with nonl
#ifdef PADENTER
			case PADENTER:  // pdcurses, used by Enter key on Windows with nonl
#endif
			case '\n':
				goto out;
			default:
				;
key_default:
				if (drv->proc_tui_handle_choice && likely(drv_ready(cgpu)))
				{
					msg = drv->proc_tui_handle_choice(cgpu, input);
					if (msg)
						goto refresh;
				}
		}
