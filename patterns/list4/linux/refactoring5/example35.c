#ifdef CONFIG_SFC_SRIOV
if ((efx->pci_dev->physfn) && (!efx->pci_dev->is_physfn)) {
		struct pci_dev *pci_dev_pf = efx->pci_dev->physfn;
		struct efx_nic *efx_pf = pci_get_drvdata(pci_dev_pf);

		efx_pf->type->get_mac_address(efx_pf, nic_data->port_id);
	} else
#endif
		ether_addr_copy(nic_data->port_id, efx->net_dev->perm_addr);
