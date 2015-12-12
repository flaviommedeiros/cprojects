#ifdef CONFIG_IP_VS_IPV6
if (cp->af == AF_INET6) {
		p += sizeof(struct ip_vs_sync_v6);
		s->v6.caddr = cp->caddr.in6;
		s->v6.vaddr = cp->vaddr.in6;
		s->v6.daddr = cp->daddr.in6;
	} else
#endif
	{
		p += sizeof(struct ip_vs_sync_v4);	/* options ptr */
		s->v4.caddr = cp->caddr.ip;
		s->v4.vaddr = cp->vaddr.ip;
		s->v4.daddr = cp->daddr.ip;
	}
