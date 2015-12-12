switch (current_cpu_data.processor_id & 0xff00) {
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
