#ifdef CONFIG_CARDBUS
if (s->state & SOCKET_CARDBUS)
			read_cb_mem(s, cis->attr, cis->addr, len, buf);
		else
#endif
			pcmcia_read_cis_mem(s, cis->attr, cis->addr, len, buf);
