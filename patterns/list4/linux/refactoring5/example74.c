#ifdef CONFIG_PCI
if (asc_dvc->bus_type & ASC_IS_PCI) {
		cfg_msw &= 0xFFC0;
		AscSetChipCfgMsw(iop_base, cfg_msw);
		if ((asc_dvc->bus_type & ASC_IS_PCI_ULTRA) == ASC_IS_PCI_ULTRA) {
		} else {
			if ((pdev->device == PCI_DEVICE_ID_ASP_1200A) ||
			    (pdev->device == PCI_DEVICE_ID_ASP_ABP940)) {
				asc_dvc->bug_fix_cntl |= ASC_BUG_FIX_IF_NOT_DWB;
				asc_dvc->bug_fix_cntl |=
				    ASC_BUG_FIX_ASYN_USE_SYN;
			}
		}
	} else
#endif /* CONFIG_PCI */
	if (asc_dvc->bus_type == ASC_IS_ISAPNP) {
		if (AscGetChipVersion(iop_base, asc_dvc->bus_type)
		    == ASC_CHIP_VER_ASYN_BUG) {
			asc_dvc->bug_fix_cntl |= ASC_BUG_FIX_ASYN_USE_SYN;
		}
	}
