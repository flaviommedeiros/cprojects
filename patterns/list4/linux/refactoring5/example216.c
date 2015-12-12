#ifdef CONFIG_IP_VS_IPV6
if (cp->af == AF_INET6)
			seq_printf(seq, "%-3s %pI6 %04X %pI6 %04X "
				"%s %04X %-11s %7lu%s\n",
				ip_vs_proto_name(cp->protocol),
				&cp->caddr.in6, ntohs(cp->cport),
				&cp->vaddr.in6, ntohs(cp->vport),
				dbuf, ntohs(cp->dport),
				ip_vs_state_name(cp->protocol, cp->state),
				(cp->timer.expires-jiffies)/HZ, pe_data);
		else
#endif
			seq_printf(seq,
				"%-3s %08X %04X %08X %04X"
				" %s %04X %-11s %7lu%s\n",
				ip_vs_proto_name(cp->protocol),
				ntohl(cp->caddr.ip), ntohs(cp->cport),
				ntohl(cp->vaddr.ip), ntohs(cp->vport),
				dbuf, ntohs(cp->dport),
				ip_vs_state_name(cp->protocol, cp->state),
				(cp->timer.expires-jiffies)/HZ, pe_data);
