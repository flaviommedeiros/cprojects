#ifdef CONFIG_PPC64
if (ASIC_IS_RN50(rdev))
			rdev->mode_info.connector_table = CT_RN50_POWER;
		else
#endif
			rdev->mode_info.connector_table = CT_GENERIC;
