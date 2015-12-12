switch (current_cpu_data.processor_id & PRID_IMP_MASK) {
#ifdef CONFIG_DT_XLP_RVP
		case PRID_IMP_NETLOGIC_XLP5XX:
			fdtp = __dtb_xlp_rvp_begin;
			break;
#endif
#ifdef CONFIG_DT_XLP_GVP
		case PRID_IMP_NETLOGIC_XLP9XX:
			fdtp = __dtb_xlp_gvp_begin;
			break;
#endif
#ifdef CONFIG_DT_XLP_FVP
		case PRID_IMP_NETLOGIC_XLP2XX:
			fdtp = __dtb_xlp_fvp_begin;
			break;
#endif
#ifdef CONFIG_DT_XLP_SVP
		case PRID_IMP_NETLOGIC_XLP3XX:
			fdtp = __dtb_xlp_svp_begin;
			break;
#endif
#ifdef CONFIG_DT_XLP_EVP
		case PRID_IMP_NETLOGIC_XLP8XX:
			fdtp = __dtb_xlp_evp_begin;
			break;
#endif
		default:
			/* Pick a built-in if any, and hope for the best */
			fdtp = __dtb_start;
			break;
		}
