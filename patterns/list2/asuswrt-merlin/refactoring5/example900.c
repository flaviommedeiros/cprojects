#ifdef CONFIG_REMOTE_DEBUG
if (channel == DEBUG_PORT) {
		while (char_count--) {
			data = base_addr[CyRDR];
			queueDebugChar(data);
		}
	} else
#endif
		/* if there is nowhere to put the data, discard it */
	if (info->tty == 0) {
		while (char_count--) {
			data = base_addr[CyRDR];
		}
	} else {		/* there is an open port for this data */
		tty = info->tty;
		/* load # characters available from the chip */

#ifdef CYCLOM_ENABLE_MONITORING
		++info->mon.int_count;
		info->mon.char_count += char_count;
		if (char_count > info->mon.char_max)
			info->mon.char_max = char_count;
		info->mon.char_last = char_count;
#endif
		len = tty_buffer_request_room(tty, char_count);
		while (len--) {
			data = base_addr[CyRDR];
			tty_insert_flip_char(tty, data, TTY_NORMAL);
#ifdef CYCLOM_16Y_HACK
			udelay(10L);
#endif
		}
		tty_schedule_flip(tty);
	}
