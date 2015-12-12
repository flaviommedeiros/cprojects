#ifdef CONFIG_SCSI_SAS_ATA
if ((phy->attached_tproto & SAS_PROTOCOL_STP) || phy->attached_sata_dev) {
		res = sas_get_ata_info(child, phy);
		if (res)
			goto out_free;

		sas_init_dev(child);
		res = sas_ata_init(child);
		if (res)
			goto out_free;
		rphy = sas_end_device_alloc(phy->port);
		if (!rphy)
			goto out_free;

		child->rphy = rphy;
		get_device(&rphy->dev);

		list_add_tail(&child->disco_list_node, &parent->port->disco_list);

		res = sas_discover_sata(child);
		if (res) {
			SAS_DPRINTK("sas_discover_sata() for device %16llx at "
				    "%016llx:0x%x returned 0x%x\n",
				    SAS_ADDR(child->sas_addr),
				    SAS_ADDR(parent->sas_addr), phy_id, res);
			goto out_list_del;
		}
	} else
#endif
	  if (phy->attached_tproto & SAS_PROTOCOL_SSP) {
		child->dev_type = SAS_END_DEV;
		rphy = sas_end_device_alloc(phy->port);
		/* FIXME: error handling */
		if (unlikely(!rphy))
			goto out_free;
		child->tproto = phy->attached_tproto;
		sas_init_dev(child);

		child->rphy = rphy;
		get_device(&rphy->dev);
		sas_fill_in_rphy(child, rphy);

		list_add_tail(&child->disco_list_node, &parent->port->disco_list);

		res = sas_discover_end_dev(child);
		if (res) {
			SAS_DPRINTK("sas_discover_end_dev() for device %16llx "
				    "at %016llx:0x%x returned 0x%x\n",
				    SAS_ADDR(child->sas_addr),
				    SAS_ADDR(parent->sas_addr), phy_id, res);
			goto out_list_del;
		}
	} else {
		SAS_DPRINTK("target proto 0x%x at %016llx:0x%x not handled\n",
			    phy->attached_tproto, SAS_ADDR(parent->sas_addr),
			    phy_id);
		goto out_free;
	}
