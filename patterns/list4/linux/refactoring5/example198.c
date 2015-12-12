#ifdef CONFIG_IP_VS_IPV6
if (dest->af == AF_INET6)
				seq_printf(seq,
					   "  -> [%pI6]:%04X"
					   "      %-7s %-6d %-10d %-10d\n",
					   &dest->addr.in6,
					   ntohs(dest->port),
					   ip_vs_fwd_name(atomic_read(&dest->conn_flags)),
					   atomic_read(&dest->weight),
					   atomic_read(&dest->activeconns),
					   atomic_read(&dest->inactconns));
			else
#endif
				seq_printf(seq,
					   "  -> %08X:%04X      "
					   "%-7s %-6d %-10d %-10d\n",
					   ntohl(dest->addr.ip),
					   ntohs(dest->port),
					   ip_vs_fwd_name(atomic_read(&dest->conn_flags)),
					   atomic_read(&dest->weight),
					   atomic_read(&dest->activeconns),
					   atomic_read(&dest->inactconns));
