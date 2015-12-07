#ifdef	CONFIG_HISAX_EURO
if (st->protocol == ISDN_PTYPE_EURO) {
		setstack_dss1(st);
	} else
#endif
#ifdef  CONFIG_HISAX_NI1
	if (st->protocol == ISDN_PTYPE_NI1) {
		setstack_ni1(st);
	} else
#endif
#ifdef	CONFIG_HISAX_1TR6
	if (st->protocol == ISDN_PTYPE_1TR6) {
		setstack_1tr6(st);
	} else
#endif
	if (st->protocol == ISDN_PTYPE_LEASED) {
		st->lli.l4l3 = no_l3_proto;
		st->l2.l2l3 = no_l3_proto;
                st->l3.l3ml3 = no_l3_proto;
		printk(KERN_INFO "HiSax: Leased line mode\n");
	} else {
		st->lli.l4l3 = no_l3_proto;
		st->l2.l2l3 = no_l3_proto;
                st->l3.l3ml3 = no_l3_proto;
		sprintf(tmp, "protocol %s not supported",
			(st->protocol == ISDN_PTYPE_1TR6) ? "1tr6" :
			(st->protocol == ISDN_PTYPE_EURO) ? "euro" :
			(st->protocol == ISDN_PTYPE_NI1) ? "ni1" :
			"unknown");
		printk(KERN_WARNING "HiSax: %s\n", tmp);
		st->protocol = -1;
	}
