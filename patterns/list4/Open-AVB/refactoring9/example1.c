static int igb_ndo_fdb_add(struct ndmsg *ndm, struct nlattr *tb[],
			   struct net_device *dev,
			   const unsigned char *addr,
#ifdef HAVE_NDO_FDB_ADD_VID
			   u16 vid,
#endif
			   u16 flags)
#else /* USE_CONST_DEV_UC_CHAR */
static int igb_ndo_fdb_add(struct ndmsg *ndm,
			   struct net_device *dev,
			   unsigned char *addr,
			   u16 flags)
#endif /* USE_CONST_DEV_UC_CHAR */
{
	struct igb_adapter *adapter = netdev_priv(dev);
	struct e1000_hw *hw = &adapter->hw;
	int err;

	if (!(adapter->vfs_allocated_count))
		return -EOPNOTSUPP;

	/* Hardware does not support aging addresses so if a
	 * ndm_state is given only allow permanent addresses
	 */
	if (ndm->ndm_state && !(ndm->ndm_state & NUD_PERMANENT)) {
		pr_info("%s: FDB only supports static addresses\n",
			igb_driver_name);
		return -EINVAL;
	}

	if (is_unicast_ether_addr(addr) || is_link_local_ether_addr(addr)) {
		u32 rar_uc_entries = hw->mac.rar_entry_count -
					(adapter->vfs_allocated_count + 1);

		if (netdev_uc_count(dev) < rar_uc_entries)
			err = dev_uc_add_excl(dev, addr);
		else
			err = -ENOMEM;
	} else if (is_multicast_ether_addr(addr)) {
		err = dev_mc_add_excl(dev, addr);
	} else {
		err = -EINVAL;
	}

	/* Only return duplicate errors if NLM_F_EXCL is set */
	if (err == -EEXIST && !(flags & NLM_F_EXCL))
		err = 0;

	return err;
}
