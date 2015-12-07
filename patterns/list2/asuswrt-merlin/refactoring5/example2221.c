#ifdef CONFIG_PPC_PMAC
if (of_machine_is_compatible("PowerBook3,3")) {
			/* powerbook with VGA */
			rdev->mode_info.connector_table = CT_POWERBOOK_VGA;
		} else if (of_machine_is_compatible("PowerBook3,4") ||
			   of_machine_is_compatible("PowerBook3,5")) {
			/* powerbook with internal tmds */
			rdev->mode_info.connector_table = CT_POWERBOOK_INTERNAL;
		} else if (of_machine_is_compatible("PowerBook5,1") ||
			   of_machine_is_compatible("PowerBook5,2") ||
			   of_machine_is_compatible("PowerBook5,3") ||
			   of_machine_is_compatible("PowerBook5,4") ||
			   of_machine_is_compatible("PowerBook5,5")) {
			/* powerbook with external single link tmds (sil164) */
			rdev->mode_info.connector_table = CT_POWERBOOK_EXTERNAL;
		} else if (of_machine_is_compatible("PowerBook5,6")) {
			/* powerbook with external dual or single link tmds */
			rdev->mode_info.connector_table = CT_POWERBOOK_EXTERNAL;
		} else if (of_machine_is_compatible("PowerBook5,7") ||
			   of_machine_is_compatible("PowerBook5,8") ||
			   of_machine_is_compatible("PowerBook5,9")) {
			/* PowerBook6,2 ? */
			/* powerbook with external dual link tmds (sil1178?) */
			rdev->mode_info.connector_table = CT_POWERBOOK_EXTERNAL;
		} else if (of_machine_is_compatible("PowerBook4,1") ||
			   of_machine_is_compatible("PowerBook4,2") ||
			   of_machine_is_compatible("PowerBook4,3") ||
			   of_machine_is_compatible("PowerBook6,3") ||
			   of_machine_is_compatible("PowerBook6,5") ||
			   of_machine_is_compatible("PowerBook6,7")) {
			/* ibook */
			rdev->mode_info.connector_table = CT_IBOOK;
		} else if (of_machine_is_compatible("PowerMac4,4")) {
			/* emac */
			rdev->mode_info.connector_table = CT_EMAC;
		} else if (of_machine_is_compatible("PowerMac10,1")) {
			/* mini with internal tmds */
			rdev->mode_info.connector_table = CT_MINI_INTERNAL;
		} else if (of_machine_is_compatible("PowerMac10,2")) {
			/* mini with external tmds */
			rdev->mode_info.connector_table = CT_MINI_EXTERNAL;
		} else if (of_machine_is_compatible("PowerMac12,1")) {
			/* PowerMac8,1 ? */
			/* imac g5 isight */
			rdev->mode_info.connector_table = CT_IMAC_G5_ISIGHT;
		} else if ((rdev->pdev->device == 0x4a48) &&
			   (rdev->pdev->subsystem_vendor == 0x1002) &&
			   (rdev->pdev->subsystem_device == 0x4a48)) {
			/* Mac X800 */
			rdev->mode_info.connector_table = CT_MAC_X800;
		} else
#endif /* CONFIG_PPC_PMAC */
#ifdef CONFIG_PPC64
		if (ASIC_IS_RN50(rdev))
			rdev->mode_info.connector_table = CT_RN50_POWER;
		else
#endif
			rdev->mode_info.connector_table = CT_GENERIC;
