static void rc_receive(struct riscom_board const *bp)
{
	struct riscom_port *port;
	struct tty_struct *tty;
	unsigned char count;

	port = rc_get_port(bp, "Receive");
	if (port == NULL)
		return;

	tty = tty_port_tty_get(&port->port);

	count = rc_in(bp, CD180_RDCR);

#ifdef RC_REPORT_FIFO
	port->hits[count > 8 ? 9 : count]++;
#endif

	while (count--)  {
		u8 ch = rc_in(bp, CD180_RDR);
		if (tty)
			tty_insert_flip_char(tty, ch, TTY_NORMAL);
	}
	if (tty) {
		tty_flip_buffer_push(tty);
		tty_kref_put(tty);
	}
}
