switch(type){
		/* We need these for the !CONFIG_MODULES case,
		   because symbol_get() doesn't work there */
#ifdef CONFIG_MTD_CFI_INTELEXT
	case P_ID_INTEL_EXT:
	case P_ID_INTEL_STD:
	case P_ID_INTEL_PERFORMANCE:
		return cfi_cmdset_0001(map, primary);
#endif
#ifdef CONFIG_MTD_CFI_AMDSTD
	case P_ID_AMD_STD:
	case P_ID_SST_OLD:
	case P_ID_WINBOND:
		return cfi_cmdset_0002(map, primary);
#endif
#ifdef CONFIG_MTD_CFI_STAA
        case P_ID_ST_ADV:
		return cfi_cmdset_0020(map, primary);
#endif
	default:
		return cfi_cmdset_unknown(map, primary);
	}
