#ifdef CONFIG_CARDBUS
if (s->state & SOCKET_CARDBUS)
	ret = read_cb_mem(s, attr, addr, len, ptr);
    else
#endif
	ret = pcmcia_read_cis_mem(s, attr, addr, len, ptr);
