switch (version) {
#ifdef CONFIG_SERIAL_UARTLITE_CONSOLE
		case UARTLITE:
			printk(KERN_INFO "Early console on uartlite "
						"at 0x%08x\n", base_addr);
			early_console = &early_serial_uartlite_console;
			break;
#endif
#ifdef CONFIG_SERIAL_8250_CONSOLE
		case UART16550:
			printk(KERN_INFO "Early console on uart16650 "
						"at 0x%08x\n", base_addr);
			early_console = &early_serial_uart16550_console;
			break;
#endif
		default:
			printk(KERN_INFO  "Unsupported early console %d\n",
								version);
			return 1;
		}
