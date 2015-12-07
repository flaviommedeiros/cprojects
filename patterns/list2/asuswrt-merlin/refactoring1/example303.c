if (info->baud_base == SERIAL_PRESCALE_BASE) {
			/* 0, 2-65535 (0=65536) */
			u16 divisor = info->custom_divisor;
			/* R_SERIAL_PRESCALE (upper 16 bits of R_CLOCK_PRESCALE) */
			/* baudrate is 3.125MHz/custom_divisor */
			alt_source =
				IO_STATE(R_ALT_SER_BAUDRATE, ser0_rec, prescale) |
				IO_STATE(R_ALT_SER_BAUDRATE, ser0_tr, prescale);
			alt_source = 0x11;
			DBAUD(printk("Writing SERIAL_PRESCALE: divisor %i\n", divisor));
			*R_SERIAL_PRESCALE = divisor;
			info->baud = SERIAL_PRESCALE_BASE/divisor;
		}
#ifdef CONFIG_ETRAX_EXTERN_PB6CLK_ENABLED
		else if ((info->baud_base==CONFIG_ETRAX_EXTERN_PB6CLK_FREQ/8 &&
			  info->custom_divisor == 1) ||
			 (info->baud_base==CONFIG_ETRAX_EXTERN_PB6CLK_FREQ &&
			  info->custom_divisor == 8)) {
				/* ext_clk selected */
				alt_source =
					IO_STATE(R_ALT_SER_BAUDRATE, ser0_rec, extern) |
					IO_STATE(R_ALT_SER_BAUDRATE, ser0_tr, extern);
				DBAUD(printk("using external baudrate: %lu\n", CONFIG_ETRAX_EXTERN_PB6CLK_FREQ/8));
				info->baud = CONFIG_ETRAX_EXTERN_PB6CLK_FREQ/8;
			}
#endif
