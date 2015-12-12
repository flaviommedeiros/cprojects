static const struct genl_ops nl802154_ops[] = {
	{
		.cmd = NL802154_CMD_GET_WPAN_PHY,
		.doit = nl802154_get_wpan_phy,
		.dumpit = nl802154_dump_wpan_phy,
		.done = nl802154_dump_wpan_phy_done,
		.policy = nl802154_policy,
		/* can be retrieved by unprivileged users */
		.internal_flags = NL802154_FLAG_NEED_WPAN_PHY |
				  NL802154_FLAG_NEED_RTNL,
	},
	{
		.cmd = NL802154_CMD_GET_INTERFACE,
		.doit = nl802154_get_interface,
		.dumpit = nl802154_dump_interface,
		.policy = nl802154_policy,
		/* can be retrieved by unprivileged users */
		.internal_flags = NL802154_FLAG_NEED_WPAN_DEV |
				  NL802154_FLAG_NEED_RTNL,
	},
	{
		.cmd = NL802154_CMD_NEW_INTERFACE,
		.doit = nl802154_new_interface,
		.policy = nl802154_policy,
		.flags = GENL_ADMIN_PERM,
		.internal_flags = NL802154_FLAG_NEED_WPAN_PHY |
				  NL802154_FLAG_NEED_RTNL,
	},
	{
		.cmd = NL802154_CMD_DEL_INTERFACE,
		.doit = nl802154_del_interface,
		.policy = nl802154_policy,
		.flags = GENL_ADMIN_PERM,
		.internal_flags = NL802154_FLAG_NEED_WPAN_DEV |
				  NL802154_FLAG_NEED_RTNL,
	},
	{
		.cmd = NL802154_CMD_SET_CHANNEL,
		.doit = nl802154_set_channel,
		.policy = nl802154_policy,
		.flags = GENL_ADMIN_PERM,
		.internal_flags = NL802154_FLAG_NEED_WPAN_PHY |
				  NL802154_FLAG_NEED_RTNL,
	},
	{
		.cmd = NL802154_CMD_SET_CCA_MODE,
		.doit = nl802154_set_cca_mode,
		.policy = nl802154_policy,
		.flags = GENL_ADMIN_PERM,
		.internal_flags = NL802154_FLAG_NEED_WPAN_PHY |
				  NL802154_FLAG_NEED_RTNL,
	},
	{
		.cmd = NL802154_CMD_SET_CCA_ED_LEVEL,
		.doit = nl802154_set_cca_ed_level,
		.policy = nl802154_policy,
		.flags = GENL_ADMIN_PERM,
		.internal_flags = NL802154_FLAG_NEED_WPAN_PHY |
				  NL802154_FLAG_NEED_RTNL,
	},
	{
		.cmd = NL802154_CMD_SET_TX_POWER,
		.doit = nl802154_set_tx_power,
		.policy = nl802154_policy,
		.flags = GENL_ADMIN_PERM,
		.internal_flags = NL802154_FLAG_NEED_WPAN_PHY |
				  NL802154_FLAG_NEED_RTNL,
	},
	{
		.cmd = NL802154_CMD_SET_PAN_ID,
		.doit = nl802154_set_pan_id,
		.policy = nl802154_policy,
		.flags = GENL_ADMIN_PERM,
		.internal_flags = NL802154_FLAG_NEED_NETDEV |
				  NL802154_FLAG_NEED_RTNL,
	},
	{
		.cmd = NL802154_CMD_SET_SHORT_ADDR,
		.doit = nl802154_set_short_addr,
		.policy = nl802154_policy,
		.flags = GENL_ADMIN_PERM,
		.internal_flags = NL802154_FLAG_NEED_NETDEV |
				  NL802154_FLAG_NEED_RTNL,
	},
	{
		.cmd = NL802154_CMD_SET_BACKOFF_EXPONENT,
		.doit = nl802154_set_backoff_exponent,
		.policy = nl802154_policy,
		.flags = GENL_ADMIN_PERM,
		.internal_flags = NL802154_FLAG_NEED_NETDEV |
				  NL802154_FLAG_NEED_RTNL,
	},
	{
		.cmd = NL802154_CMD_SET_MAX_CSMA_BACKOFFS,
		.doit = nl802154_set_max_csma_backoffs,
		.policy = nl802154_policy,
		.flags = GENL_ADMIN_PERM,
		.internal_flags = NL802154_FLAG_NEED_NETDEV |
				  NL802154_FLAG_NEED_RTNL,
	},
	{
		.cmd = NL802154_CMD_SET_MAX_FRAME_RETRIES,
		.doit = nl802154_set_max_frame_retries,
		.policy = nl802154_policy,
		.flags = GENL_ADMIN_PERM,
		.internal_flags = NL802154_FLAG_NEED_NETDEV |
				  NL802154_FLAG_NEED_RTNL,
	},
	{
		.cmd = NL802154_CMD_SET_LBT_MODE,
		.doit = nl802154_set_lbt_mode,
		.policy = nl802154_policy,
		.flags = GENL_ADMIN_PERM,
		.internal_flags = NL802154_FLAG_NEED_NETDEV |
				  NL802154_FLAG_NEED_RTNL,
	},
	{
		.cmd = NL802154_CMD_SET_ACKREQ_DEFAULT,
		.doit = nl802154_set_ackreq_default,
		.policy = nl802154_policy,
		.flags = GENL_ADMIN_PERM,
		.internal_flags = NL802154_FLAG_NEED_NETDEV |
				  NL802154_FLAG_NEED_RTNL,
	},
#ifdef CONFIG_IEEE802154_NL802154_EXPERIMENTAL
	{
		.cmd = NL802154_CMD_SET_SEC_PARAMS,
		.doit = nl802154_set_llsec_params,
		.policy = nl802154_policy,
		.flags = GENL_ADMIN_PERM,
		.internal_flags = NL802154_FLAG_NEED_NETDEV |
				  NL802154_FLAG_NEED_RTNL,
	},
	{
		.cmd = NL802154_CMD_GET_SEC_KEY,
		/* TODO .doit by matching key id? */
		.dumpit = nl802154_dump_llsec_key,
		.policy = nl802154_policy,
		.flags = GENL_ADMIN_PERM,
		.internal_flags = NL802154_FLAG_NEED_NETDEV |
				  NL802154_FLAG_NEED_RTNL,
	},
	{
		.cmd = NL802154_CMD_NEW_SEC_KEY,
		.doit = nl802154_add_llsec_key,
		.policy = nl802154_policy,
		.flags = GENL_ADMIN_PERM,
		.internal_flags = NL802154_FLAG_NEED_NETDEV |
				  NL802154_FLAG_NEED_RTNL,
	},
	{
		.cmd = NL802154_CMD_DEL_SEC_KEY,
		.doit = nl802154_del_llsec_key,
		.policy = nl802154_policy,
		.flags = GENL_ADMIN_PERM,
		.internal_flags = NL802154_FLAG_NEED_NETDEV |
				  NL802154_FLAG_NEED_RTNL,
	},
	/* TODO unique identifier must short+pan OR extended_addr */
	{
		.cmd = NL802154_CMD_GET_SEC_DEV,
		/* TODO .doit by matching extended_addr? */
		.dumpit = nl802154_dump_llsec_dev,
		.policy = nl802154_policy,
		.flags = GENL_ADMIN_PERM,
		.internal_flags = NL802154_FLAG_NEED_NETDEV |
				  NL802154_FLAG_NEED_RTNL,
	},
	{
		.cmd = NL802154_CMD_NEW_SEC_DEV,
		.doit = nl802154_add_llsec_dev,
		.policy = nl802154_policy,
		.flags = GENL_ADMIN_PERM,
		.internal_flags = NL802154_FLAG_NEED_NETDEV |
				  NL802154_FLAG_NEED_RTNL,
	},
	{
		.cmd = NL802154_CMD_DEL_SEC_DEV,
		.doit = nl802154_del_llsec_dev,
		.policy = nl802154_policy,
		.flags = GENL_ADMIN_PERM,
		.internal_flags = NL802154_FLAG_NEED_NETDEV |
				  NL802154_FLAG_NEED_RTNL,
	},
	/* TODO remove complete devkey, put it as nested? */
	{
		.cmd = NL802154_CMD_GET_SEC_DEVKEY,
		/* TODO doit by matching ??? */
		.dumpit = nl802154_dump_llsec_devkey,
		.policy = nl802154_policy,
		.flags = GENL_ADMIN_PERM,
		.internal_flags = NL802154_FLAG_NEED_NETDEV |
				  NL802154_FLAG_NEED_RTNL,
	},
	{
		.cmd = NL802154_CMD_NEW_SEC_DEVKEY,
		.doit = nl802154_add_llsec_devkey,
		.policy = nl802154_policy,
		.flags = GENL_ADMIN_PERM,
		.internal_flags = NL802154_FLAG_NEED_NETDEV |
				  NL802154_FLAG_NEED_RTNL,
	},
	{
		.cmd = NL802154_CMD_DEL_SEC_DEVKEY,
		.doit = nl802154_del_llsec_devkey,
		.policy = nl802154_policy,
		.flags = GENL_ADMIN_PERM,
		.internal_flags = NL802154_FLAG_NEED_NETDEV |
				  NL802154_FLAG_NEED_RTNL,
	},
	{
		.cmd = NL802154_CMD_GET_SEC_LEVEL,
		/* TODO .doit by matching frame_type? */
		.dumpit = nl802154_dump_llsec_seclevel,
		.policy = nl802154_policy,
		.flags = GENL_ADMIN_PERM,
		.internal_flags = NL802154_FLAG_NEED_NETDEV |
				  NL802154_FLAG_NEED_RTNL,
	},
	{
		.cmd = NL802154_CMD_NEW_SEC_LEVEL,
		.doit = nl802154_add_llsec_seclevel,
		.policy = nl802154_policy,
		.flags = GENL_ADMIN_PERM,
		.internal_flags = NL802154_FLAG_NEED_NETDEV |
				  NL802154_FLAG_NEED_RTNL,
	},
	{
		.cmd = NL802154_CMD_DEL_SEC_LEVEL,
		/* TODO match frame_type only? */
		.doit = nl802154_del_llsec_seclevel,
		.policy = nl802154_policy,
		.flags = GENL_ADMIN_PERM,
		.internal_flags = NL802154_FLAG_NEED_NETDEV |
				  NL802154_FLAG_NEED_RTNL,
	},
#endif /* CONFIG_IEEE802154_NL802154_EXPERIMENTAL */
};
