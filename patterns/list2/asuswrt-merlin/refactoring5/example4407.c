#ifdef	SUPPORT_LPRng
if (nvram_match("usr_timeout", "1")) {
			int timeout;
			timeout = atoi(nvram_safe_get("usr_timeout_ctrl"));
			timeout_control_msg = timeout <= 0 ? 1000 : timeout;
			timeout = atoi(nvram_safe_get("usr_timeout_br"));
			timeout_bulk_read_msg = timeout <= 0 ? 5000 : timeout;
			timeout = atoi(nvram_safe_get("usr_timeout_bw"));
			timeout_bulk_write_msg = timeout <= 0 ? 5000 : timeout;
		} else
#endif
#endif
		if (Is_EPSON) {					// EPSON
			timeout_control_msg = 100;
			if (single_interface)
				timeout_bulk_read_msg = 5000;
			else
				timeout_bulk_read_msg = 30000;
			timeout_bulk_write_msg = 5000;
		}
		else if (Is_Lexmark) {				// Lexmark
			timeout_control_msg = 10;
			timeout_bulk_read_msg = 100;
			timeout_bulk_write_msg = 100;
		}
		else if (Is_HP) {				// HP
			timeout_control_msg = 1000;
			if (dev->descriptor.idProduct == 0x4117)// HP LaserJet 1018 
				timeout_bulk_read_msg =1000;
			else if (single_interface)
				timeout_bulk_read_msg = 5000;
			else
				timeout_bulk_read_msg = 15000;

//			timeout_bulk_write_msg = 5000;
			timeout_bulk_write_msg = 32767;		// magic number for no timeout
		}
		else if (Is_Canon) {				// Canon
			timeout_control_msg = 100;
			timeout_bulk_read_msg = 30000;
			timeout_bulk_write_msg = 1000;
		}
		else {						// for general printers
			timeout_control_msg = 1000;
			if (single_interface)
				timeout_bulk_read_msg = 5000;
			else
				timeout_bulk_read_msg = 10000;
			timeout_bulk_write_msg = 5000;
		}
