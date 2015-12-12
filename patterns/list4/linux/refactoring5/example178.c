#ifdef CONFIG_IP_ROUTE_MULTIPATH
if (res->fi->fib_nhs > 1 && fl4->flowi4_oif == 0) {
		if (mp_hash < 0)
			mp_hash = get_hash_from_flowi4(fl4) >> 1;

		fib_select_multipath(res, mp_hash);
	}
	else
#endif
	if (!res->prefixlen &&
	    res->table->tb_num_default > 1 &&
	    res->type == RTN_UNICAST && !fl4->flowi4_oif)
		fib_select_default(fl4, res);
