#ifdef CONFIG_SCSI_SAS_ATA
if ((phy->attached_tproto & SAS_PROTOCOL_STP) || phy->attached_sata_dev) {
		child->dev_type = SATA_DEV;
		if (phy->attached_tproto & SAS_PROTOCOL_STP)
			child->tproto = phy->attached_tproto;
		if (phy->attached_sata_dev)
			child->tproto |= SATA_DEV;
		res = sas_get_report_phy_sata(parent, phy_id,
					      &child->sata_dev.rps_resp);
		if (res) {
			SAS_DPRINTK("report phy sata to %016llx:0x%x returned "
				    "0x%x\n", SAS_ADDR(parent->sas_addr),
				    phy_id, res);
			goto out_free;
		}
		memcpy(child->frame_rcvd, &child->sata_dev.rps_resp.rps.fis,
		       sizeof(struct dev_to_host_fis));

		rphy = sas_end_device_alloc(phy->port);
		if (unlikely(!rphy))
			goto out_free;

		sas_init_dev(child);

		child->rphy = rphy;

		spin_lock_irq(&parent->port->dev_list_lock);
		list_add_tail(&child->dev_list_node, &parent->port->dev_list);
		spin_unlock_irq(&parent->port->dev_list_lock);

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
		if (unlikely(!rphy))
			goto out_free;
		child->tproto = phy->attached_tproto;
		sas_init_dev(child);

		child->rphy = rphy;
		sas_fill_in_rphy(child, rphy);

		spin_lock_irq(&parent->port->dev_list_lock);
		list_add_tail(&child->dev_list_node, &parent->port->dev_list);
		spin_unlock_irq(&parent->port->dev_list_lock);

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
