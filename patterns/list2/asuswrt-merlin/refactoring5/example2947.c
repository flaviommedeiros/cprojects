#ifndef LINUX_2_6_36
if (!insert_entry(ipt_filter_chain_name[filter->dir], ipt_target_name[fw->target], entry, &handle)) {
#else
		if (!insert_entry(ipt_filter_chain_name[filter->dir], ipt_target_name[fw->target], entry, handle)) {
#endif
#else /* LINUX26 */
		if (!insert_entry(ipt_filter_chain_name[filter->dir], entry, &handle)) {
#endif /* LINUX26 */
			fprintf(stderr, "%s\n", iptc_strerror(errno));
			goto err;
		}
	}

	/* Set NAT target information */
	else if (nat) {
#ifndef LINUX_2_6_36
		struct ip_nat_multi_range *mr = (struct ip_nat_multi_range *) &target->data[0];
		struct ip_nat_range *range = (struct ip_nat_range *) &mr->range[0];
#else
		struct nf_nat_multi_range *mr = (struct nf_nat_multi_range *) &target->data[0];
		struct nf_nat_range *range = (struct nf_nat_range *) &mr->range[0];
#endif /* linux-2.6.36 */
		
		mr->rangesize = 1;

		/* Map to IP address */
		if (nat->ipaddr.s_addr) {
			range->min_ip = range->max_ip = nat->ipaddr.s_addr;
			range->flags |= IP_NAT_RANGE_MAP_IPS;
		}

		/* Map to TCP port(s) */
		if (nat->match.ipproto == IPPROTO_TCP) {
			range->min.tcp.port = nat->ports[0];
			range->max.tcp.port = nat->ports[1];
			range->flags |= IP_NAT_RANGE_PROTO_SPECIFIED;
		}

		/* Map to UDP port(s) */
		else if (nat->match.ipproto == IPPROTO_UDP) {
			range->min.udp.port = nat->ports[0];
			range->max.udp.port = nat->ports[1];
			range->flags |= IP_NAT_RANGE_PROTO_SPECIFIED;
		}

#ifdef LINUX26
#ifndef LINUX_2_6_36
		if (!insert_entry(ipt_nat_chain_name[fw->target], ipt_target_name[fw->target], entry, &handle)) {
#else
		if (!insert_entry(ipt_nat_chain_name[fw->target], ipt_target_name[fw->target], entry, handle)) {
#endif /* linux-2.6.36 */
#else /* LINUX26 */
		if (!insert_entry(ipt_nat_chain_name[fw->target], entry, &handle)) {
#endif /* LINUX26 */
			fprintf(stderr, "%s\n", iptc_strerror(errno));
			goto err;
		}
	}

	else if (app) {
		struct ip_autofw_info *info = (struct ip_autofw_info *) &target->data[0];

		info->proto = app->proto;
		info->dport[0] = app->dport[0];
		info->dport[1] = app->dport[1];
		info->to[0] = app->to[0];
		info->to[1] = app->to[1];

#ifdef LINUX26
#ifndef LINUX_2_6_36
		if (!insert_entry("PREROUTING", ipt_target_name[fw->target], entry, &handle)) {
#else
		if (!insert_entry("PREROUTING", ipt_target_name[fw->target], entry, handle)) {
#endif /* linux-2.6.36 */
#else /* LINUX26 */
		if (!insert_entry("PREROUTING", entry, &handle)) {
#endif /* LINUX26 */
			fprintf(stderr, "%s\n", iptc_strerror(errno));
			goto err;
		}
	}

#ifndef LINUX_2_6_36
	if (!iptc_commit(&handle)) {
#else
	if (!iptc_commit(handle)) {
#endif /* linux-2.6.36 */
		fprintf(stderr, "%s\n", iptc_strerror(errno));
		goto err;
	}

#ifdef LINUX_2_6_36
	iptc_free(handle);
#endif
	free(entry);
	return 0;

 err:
	if (handle)
#ifndef LINUX_2_6_36
		iptc_commit(&handle);
#else
		iptc_commit(handle);
#endif /* linux-2.6.36 */
#ifdef LINUX_2_6_36
	if (handle)
		iptc_free(handle);
#endif
	free(entry);
	return errno;
}

/*
 * Delete a firewall entry
 * @param	fw	firewall entry
 * @return	0 on success and errno on failure
 */
int
netconf_del_fw(netconf_fw_t *fw)
{
	int num;
	const char *chain;
#ifndef LINUX_2_6_36
	iptc_handle_t handle;
#else
	struct iptc_handle *handle;
#endif /* linux-2.6.36 */

	/* netconf_fw_index() sanity checks fw */
	if ((num = netconf_fw_index(fw)) < 0)
		return -num;

	/* Pick the right chain name */
	if (netconf_valid_filter(fw->target))
		chain = ipt_filter_chain_name[((netconf_filter_t *) fw)->dir];
	else if (netconf_valid_nat(fw->target))
		chain = ipt_nat_chain_name[fw->target];
	else if (fw->target == NETCONF_APP)
		chain = "PREROUTING";
	else
		return EINVAL;
		
	/* Commit changes */
	if (!(handle = iptc_init(ipt_table_name[fw->target])) ||
#ifndef LINUX_2_6_36
	    !iptc_delete_num_entry(chain, num, &handle) ||
	    !iptc_commit(&handle)) {
#else
	    !iptc_delete_num_entry(chain, num, handle) ||
	    !iptc_commit(handle)) {
#endif /* linux-2.6.36 */
#ifdef LINUX_2_6_36
		if (handle)
			iptc_free(handle);
#endif
		fprintf(stderr, "%s\n", iptc_strerror(errno));
		return errno;
	}

#ifdef LINUX_2_6_36
	iptc_free(handle);
#endif
	return 0;
}

/*
 * Add or delete a firewall entry or list of firewall entries
 * @param	fw_list	firewall entry or list of firewall entries
 * @bool	del	whether to delete or add
 * @return	0 on success and errno on failure
 */
static int
netconf_manip_fw(netconf_fw_t *fw_list, bool del)
{
	netconf_fw_t *fw;
	int ret;

	/* Single firewall entry */
	if (netconf_list_empty(fw_list) || !fw_list->next)
		return (del ? netconf_del_fw(fw_list) : netconf_add_fw(fw_list));

	/* List of firewall entries */
	netconf_list_for_each(fw, fw_list) {
		if ((ret = del ? netconf_del_fw(fw) : netconf_add_fw(fw)))
			return ret;
	}
	
	return 0;
}

/*
 * Add a NAT entry or list of NAT entries
 * @param	nat_list	NAT entry or list of NAT entries
 * @return	0 on success and errno on failure
 */
int
netconf_add_nat(netconf_nat_t *nat_list)
{
	return netconf_manip_fw((netconf_fw_t *) nat_list, 0);
}

/*
 * Delete a NAT entry or list of NAT entries
 * @param	nat_list	NAT entry or list of NAT entries
 * @return	0 on success and errno on failure
 */
int
netconf_del_nat(netconf_nat_t *nat_list)
{
	return netconf_manip_fw((netconf_fw_t *) nat_list, 1);
}

/*
 * Get an array of the current NAT entries
 * @param	nat_array	array of NAT entries
 * @param	space		Pointer to size of nat_array in bytes
 * @return 0 on success and errno on failure
 */
int
netconf_get_nat(netconf_nat_t *nat_array, int *space)
{
	netconf_fw_t *fw, fw_list;
	int ret;
	int found = 0;
	
	if ((ret = netconf_get_fw(&fw_list)))
		return ret;
		
	netconf_list_for_each(fw, &fw_list) {
		if (netconf_valid_nat(fw->target)) {
			found++;
			if (*space && *space >= (found * sizeof(netconf_nat_t)))
				memcpy(&nat_array[found - 1], (netconf_nat_t *) fw, sizeof(netconf_nat_t));
		}
	}

	if (!*space)
		*space = found * sizeof(netconf_nat_t);

	netconf_list_free(&fw_list);
	return 0;
}			

/*
 * Add a filter entry or list of filter entries
 * @param	filter_list	filter entry or list of filter entries
 * @return	0 on success and errno on failure
 */
int
netconf_add_filter(netconf_filter_t *filter_list)
{
	return netconf_manip_fw((netconf_fw_t *) filter_list, 0);
}

/*
 * Delete a filter entry or list of filter entries
 * @param	filter_list	filter entry or list of filter entries
 * @return	0 on success and errno on failure
 */
int
netconf_del_filter(netconf_filter_t *filter_list)
{
	return netconf_manip_fw((netconf_fw_t *) filter_list, 1);
}

/*
 * Get an array of the current filter entries
 * @param	filter_array	array of filter entries
 * @param	space		Pointer to size of filter_array in bytes
 * @return 0 on success and errno on failure
 */
int
netconf_get_filter(netconf_filter_t *filter_array, int *space)
{
	netconf_fw_t *fw, fw_list;
	int ret;
	int found = 0;
	
	if ((ret = netconf_get_fw(&fw_list)))
		return ret;
		
	netconf_list_for_each(fw, &fw_list) {
		if (netconf_valid_filter(fw->target)) {
			found++;
			if (*space && *space >= (found * sizeof(netconf_filter_t)))
				memcpy(&filter_array[found - 1], (netconf_filter_t *) fw, sizeof(netconf_filter_t));
		}
	}

	if (!*space)
		*space = found * sizeof(netconf_filter_t);

	netconf_list_free(&fw_list);
	return 0;
}			

/*
 * Generates an ipt_entry with an optional match and one target
 * @param match_name		match name
 * @param match_data		match data
 * @param match_data_size	match data size
 * @param target_name		target name
 * @param target_data		target data
 * @param target_data_size	target data size
 * @return newly allocated and initialized ipt_entry
 */
static struct ipt_entry *
netconf_generate_entry(const char *match_name, const void *match_data, size_t match_data_size,
		       const char *target_name, const void *target_data, size_t target_data_size)
{
	struct ipt_entry *entry;
	struct ipt_entry_match *match;
	struct ipt_entry_target *target;

	/* Allocate entry */
	if (!(entry = calloc(1, sizeof(struct ipt_entry)))) {
		perror("calloc");
		return NULL;
	}

	/* Initialize entry parameters */
	entry->next_offset = entry->target_offset = sizeof(struct ipt_entry);

	/* Allocate space for and copy match data */
	if (match_data) {
		if (!(match = netconf_append_match(&entry, match_name, match_data_size)))
			goto err;
		memcpy(&match->data[0], match_data, match_data_size);
	}

	/* Allocate space for and copy target data */
	if (!(target = netconf_append_target(&entry, target_name, target_data_size)))
		goto err;
	memcpy(&target->data[0], target_data, target_data_size);

	return entry;

 err:
	free(entry);
	return NULL;
}

static int
netconf_reset_chain(char *table, char *chain)
{
#ifndef LINUX_2_6_36
	iptc_handle_t handle = NULL;
#else
	struct iptc_handle *handle = NULL;	
#endif /* linux-2.6.36 */

	/* Get handle to table */
	if (!(handle = iptc_init(table)))
		goto err;

	/* Create chain if necessary */
	if (!iptc_is_chain(chain, handle))
#ifndef LINUX_2_6_36
		if (!iptc_create_chain(chain, &handle))
#else
		if (!iptc_create_chain(chain, handle))
#endif /* linux-2.6.36 */
			goto err;

	/* Flush entries and commit */
#ifndef LINUX_2_6_36
	if (!iptc_flush_entries(chain, &handle) ||
	    !iptc_commit(&handle))
#else
	if (!iptc_flush_entries(chain, handle) ||
	    !iptc_commit(handle))
#endif /* linux-2.6.36 */
		goto err;

#ifdef LINUX_2_6_36
	iptc_free(handle);
#endif
	return 0;

 err:
	if (handle)
#ifndef LINUX_2_6_36
		iptc_commit(&handle);
#else
		iptc_commit(handle);
#endif /* linux-2.6.36 */
#ifdef LINUX_2_6_36
	if (handle)
		iptc_free(handle);
#endif
	fprintf(stderr, "%s\n", iptc_strerror(errno));
	return errno;
}

/*
 * Reset the firewall to a sane state
 * @return	0 on success and errno on failure
 */
int
netconf_reset_fw(void)
{
#ifndef LINUX_2_6_36
	iptc_handle_t handle = NULL;
#else
	struct iptc_handle *handle = NULL;	
#endif /* linux-2.6.36 */
	struct ipt_entry *entry = NULL;
	struct ipt_state_info state;
	struct ipt_log_info log;
	int ret, unused;

	/* Reset default chains */
	if ((ret = netconf_reset_chain("filter", "INPUT")) ||
	    (ret = netconf_reset_chain("filter", "FORWARD")) ||
	    (ret = netconf_reset_chain("filter", "OUTPUT")) ||
	    (ret = netconf_reset_chain("nat", "PREROUTING")) ||
	    (ret = netconf_reset_chain("nat", "POSTROUTING")) ||
	    (ret = netconf_reset_chain("nat", "OUTPUT")))
		return ret;

	/* Reset custom chains */
	if ((ret = netconf_reset_chain("filter", "logdrop")) ||
	    (ret = netconf_reset_chain("filter", "logaccept")))
		goto err;

	/* Log only when a connection is attempted */
	memset(&state, 0, sizeof(state));
	state.statemask = IPT_STATE_BIT(IP_CT_NEW);

	/* Set miscellaneous log parameters */
	memset(&log, 0, sizeof(log));
	log.level = LOG_WARNING;
	log.logflags = 0xf;

	/* Log packet */
	strncpy(log.prefix, "DROP ", sizeof(log.prefix));
	if (!(entry = netconf_generate_entry("state", &state, sizeof(state), "LOG", &log, sizeof(log))))
		return ENOMEM;
	entry->nfcache |= NFC_UNKNOWN;
	if (!(handle = iptc_init("filter")) ||
#ifndef LINUX_2_6_36
	    !iptc_insert_entry("logdrop", entry, 0, &handle) ||
	    !iptc_commit(&handle))
#else
	    !iptc_insert_entry("logdrop", entry, 0, handle) ||
	    !iptc_commit(handle))
#endif /* linux-2.6.36 */
		goto err;
#ifdef LINUX_2_6_36
	iptc_free(handle);
#endif
	free(entry);

	/* Drop packet */
	if (!(entry = netconf_generate_entry(NULL, NULL, 0, "DROP", &unused, sizeof(unused))))
		return ENOMEM;
	entry->nfcache |= NFC_UNKNOWN;
	if (!(handle = iptc_init("filter")) ||
#ifndef LINUX_2_6_36
	    !iptc_insert_entry("logdrop", entry, 1, &handle) ||
	    !iptc_commit(&handle))
#else
	    !iptc_insert_entry("logdrop", entry, 1, handle) ||
	    !iptc_commit(handle))
#endif /* linux-2.6.36 */
		goto err;
#ifdef LINUX_2_6_36
	iptc_free(handle);
#endif
	free(entry);

	/* Log packet */
	strncpy(log.prefix, "ACCEPT ", sizeof(log.prefix));
	if (!(entry = netconf_generate_entry("state", &state, sizeof(state), "LOG", &log, sizeof(log))))
		return ENOMEM;
	entry->nfcache |= NFC_UNKNOWN;
	if (!(handle = iptc_init("filter")) ||
#ifndef LINUX_2_6_36
	    !iptc_insert_entry("logaccept", entry, 0, &handle) ||
	    !iptc_commit(&handle))
#else
	    !iptc_insert_entry("logaccept", entry, 0, handle) ||
	    !iptc_commit(handle))
#endif /* linux-2.6.36 */
		goto err;
#ifdef LINUX_2_6_36
	iptc_free(handle);
#endif
	free(entry);

	/* Accept packet */
	if (!(entry = netconf_generate_entry(NULL, NULL, 0, "ACCEPT", &unused, sizeof(unused))))
		return ENOMEM;
	entry->nfcache |= NFC_UNKNOWN;
	if (!(handle = iptc_init("filter")) ||
#ifndef LINUX_2_6_36
	    !iptc_insert_entry("logaccept", entry, 1, &handle) ||
	    !iptc_commit(&handle))
#else
	    !iptc_insert_entry("logaccept", entry, 1, handle) ||
	    !iptc_commit(handle))
#endif /* linux-2.6.36 */
		goto err;
#ifdef LINUX_2_6_36
	iptc_free(handle);
#endif
	free(entry);

	return 0;

 err:
#ifdef LINUX_2_6_36
	if (handle)
		iptc_free(handle);
#endif
	if (entry)
		free(entry);
	fprintf(stderr, "%s\n", iptc_strerror(errno));
	return errno;
}

/* 
 * Below are miscellaneous functions that do not fit into the grand
 * scheme of netconf
 */

/*
 * Clamp TCP MSS value to PMTU of interface (for masquerading through PPPoE)
 * @return	0 on success and errno on failure
 */
int
netconf_clamp_mss_to_pmtu(void)
{
	struct ipt_entry *entry;
#ifndef LINUX_2_6_36
	iptc_handle_t handle;
#else
	struct iptc_handle *handle = NULL;
#endif /* linux-2.6.36 */
	struct ipt_tcp tcp;
	struct ipt_tcpmss_info tcpmss;

	/* Match on SYN=1 RST=0 */
	memset(&tcp, 0, sizeof(tcp));
	tcp.spts[1] = tcp.dpts[1] = 0xffff;
	tcp.flg_mask = TH_SYN | TH_RST;
	tcp.flg_cmp = TH_SYN;

	/* Clamp TCP MSS to PMTU */
	memset(&tcpmss, 0, sizeof(tcpmss));
	tcpmss.mss = IPT_TCPMSS_CLAMP_PMTU;

	/* Generate and complete the entry */
	if (!(entry = netconf_generate_entry("tcp", &tcp, sizeof(tcp), "TCPMSS", &tcpmss, sizeof(tcpmss))))
		return ENOMEM;
	entry->ip.proto = IPPROTO_TCP;
	entry->nfcache |= NFC_IP_PROTO | NFC_IP_TCPFLAGS;

	/* Do it */
	if (!(handle = iptc_init("filter")) ||
#ifndef LINUX_2_6_36
	    !iptc_insert_entry("FORWARD", entry, 0, &handle) ||
	    !iptc_commit(&handle)) {
#else
	    !iptc_insert_entry("FORWARD", entry, 0, handle) ||
	    !iptc_commit(handle)) {
#endif /* linux-2.6.36 */
#ifdef LINUX_2_6_36
		if (handle)
			iptc_free(handle);
#endif
		fprintf(stderr, "%s\n", iptc_strerror(errno));
		free(entry);
		return errno;
	}

#ifdef LINUX_2_6_36
	if (handle)
		iptc_free(handle);
#endif
	free(entry);
	return 0;
}
