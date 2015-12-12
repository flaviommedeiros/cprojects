static struct ConfEntry conf_class_table[] = {
    { "ping_time", 		CF_TIME, conf_set_class_ping_time,		0, NULL },
    { "cidr_ipv4_bitlen",	CF_INT,  conf_set_class_cidr_ipv4_bitlen,		0, NULL },
#ifdef RB_IPV6
    { "cidr_ipv6_bitlen",	CF_INT,  conf_set_class_cidr_ipv6_bitlen,		0, NULL },
#endif
    { "number_per_cidr",	CF_INT,  conf_set_class_number_per_cidr,	0, NULL },
    { "number_per_ip",	CF_INT,  conf_set_class_number_per_ip,		0, NULL },
    { "number_per_ip_global", CF_INT,conf_set_class_number_per_ip_global,	0, NULL },
    { "number_per_ident", 	CF_INT,  conf_set_class_number_per_ident,	0, NULL },
    { "connectfreq", 	CF_TIME, conf_set_class_connectfreq,		0, NULL },
    { "max_number", 	CF_INT,  conf_set_class_max_number,		0, NULL },
    { "sendq", 		CF_TIME, conf_set_class_sendq,			0, NULL },
    { "\0",	0, NULL, 0, NULL }
};
