switch (cur_cpu_spec->pmc_type) {
#ifdef HAS_PPC_PMC_IBM
	case PPC_PMC_IBM:
		attrs = ibm_common_attrs;
		nattrs = sizeof(ibm_common_attrs) / sizeof(struct device_attribute);
		pmc_attrs = classic_pmc_attrs;
		break;
#endif /* HAS_PPC_PMC_IBM */
#ifdef HAS_PPC_PMC_G4
	case PPC_PMC_G4:
		attrs = g4_common_attrs;
		nattrs = sizeof(g4_common_attrs) / sizeof(struct device_attribute);
		pmc_attrs = classic_pmc_attrs;
		break;
#endif /* HAS_PPC_PMC_G4 */
#ifdef HAS_PPC_PMC_PA6T
	case PPC_PMC_PA6T:
		/* PA Semi starts counting at PMC0 */
		attrs = pa6t_attrs;
		nattrs = sizeof(pa6t_attrs) / sizeof(struct device_attribute);
		pmc_attrs = NULL;
		break;
#endif /* HAS_PPC_PMC_PA6T */
	default:
		attrs = NULL;
		nattrs = 0;
		pmc_attrs = NULL;
	}
