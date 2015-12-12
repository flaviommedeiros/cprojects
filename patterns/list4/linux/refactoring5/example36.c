#ifdef CONFIG_SFC_SRIOV
if (efx->pci_dev->is_virtfn && efx->pci_dev->physfn) {
		struct pci_dev *pci_dev_pf = efx->pci_dev->physfn;

		if (rc == -EPERM) {
			struct efx_nic *efx_pf;

			/* Switch to PF and change MAC address on vport */
			efx_pf = pci_get_drvdata(pci_dev_pf);

			rc = efx_ef10_sriov_set_vf_mac(efx_pf,
						       nic_data->vf_index,
						       efx->net_dev->dev_addr);
		} else if (!rc) {
			struct efx_nic *efx_pf = pci_get_drvdata(pci_dev_pf);
			struct efx_ef10_nic_data *nic_data = efx_pf->nic_data;
			unsigned int i;

			/* MAC address successfully changed by VF (with MAC
			 * spoofing) so update the parent PF if possible.
			 */
			for (i = 0; i < efx_pf->vf_count; ++i) {
				struct ef10_vf *vf = nic_data->vf + i;

				if (vf->efx == efx) {
					ether_addr_copy(vf->mac,
							efx->net_dev->dev_addr);
					return 0;
				}
			}
		}
	} else
#endif
	if (rc == -EPERM) {
		netif_err(efx, drv, efx->net_dev,
			  "Cannot change MAC address; use sfboot to enable"
			  " mac-spoofing on this interface\n");
	} else if (rc == -ENOSYS && !efx_ef10_is_vf(efx)) {
		/* If the active MCFW does not support MC_CMD_VADAPTOR_SET_MAC
		 * fall-back to the method of changing the MAC address on the
		 * vport.  This only applies to PFs because such versions of
		 * MCFW do not support VFs.
		 */
		rc = efx_ef10_vport_set_mac_address(efx);
	} else {
		efx_mcdi_display_error(efx, MC_CMD_VADAPTOR_SET_MAC,
				       sizeof(inbuf), NULL, 0, rc);
	}
