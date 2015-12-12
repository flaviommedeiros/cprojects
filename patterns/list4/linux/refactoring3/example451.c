switch(macio->type) {
#ifndef CONFIG_PPC64
	    case macio_grand_central:
		pmac_mb.model_id = PMAC_TYPE_PSURGE;
		pmac_mb.model_name = "Unknown PowerSurge";
		break;
	    case macio_ohare:
		pmac_mb.model_id = PMAC_TYPE_UNKNOWN_OHARE;
		pmac_mb.model_name = "Unknown OHare-based";
		break;
	    case macio_heathrow:
		pmac_mb.model_id = PMAC_TYPE_UNKNOWN_HEATHROW;
		pmac_mb.model_name = "Unknown Heathrow-based";
		pmac_mb.features = heathrow_desktop_features;
		break;
	    case macio_paddington:
		pmac_mb.model_id = PMAC_TYPE_UNKNOWN_PADDINGTON;
		pmac_mb.model_name = "Unknown Paddington-based";
		pmac_mb.features = paddington_features;
		break;
	    case macio_keylargo:
		pmac_mb.model_id = PMAC_TYPE_UNKNOWN_CORE99;
		pmac_mb.model_name = "Unknown Keylargo-based";
		pmac_mb.features = core99_features;
		break;
	    case macio_pangea:
		pmac_mb.model_id = PMAC_TYPE_UNKNOWN_PANGEA;
		pmac_mb.model_name = "Unknown Pangea-based";
		pmac_mb.features = pangea_features;
		break;
	    case macio_intrepid:
		pmac_mb.model_id = PMAC_TYPE_UNKNOWN_INTREPID;
		pmac_mb.model_name = "Unknown Intrepid-based";
		pmac_mb.features = intrepid_features;
		break;
#else /* CONFIG_PPC64 */
	case macio_keylargo2:
		pmac_mb.model_id = PMAC_TYPE_UNKNOWN_K2;
		pmac_mb.model_name = "Unknown K2-based";
		pmac_mb.features = g5_features;
		break;
	case macio_shasta:
		pmac_mb.model_id = PMAC_TYPE_UNKNOWN_SHASTA;
		pmac_mb.model_name = "Unknown Shasta-based";
		pmac_mb.features = g5_features;
		break;
#endif /* CONFIG_PPC64 */
	default:
		ret = -ENODEV;
		goto done;
	}
