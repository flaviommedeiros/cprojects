static struct bat_attribute *mesh_attrs[] = {
	&bat_attr_aggregated_ogms,
	&bat_attr_bonding,
	&bat_attr_fragmentation,
	&bat_attr_ap_isolation,
	&bat_attr_vis_mode,
	&bat_attr_routing_algo,
	&bat_attr_gw_mode,
	&bat_attr_orig_interval,
	&bat_attr_hop_penalty,
	&bat_attr_gw_sel_class,
	&bat_attr_gw_bandwidth,
#ifdef CONFIG_BATMAN_ADV_DEBUG
	&bat_attr_log_level,
#endif
	NULL,
};
