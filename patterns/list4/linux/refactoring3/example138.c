switch (vsi->type) {
			case I40E_VSI_MAIN:
				qcount = min_t(int, pf->rss_size, num_tc_qps);
				break;
#ifdef I40E_FCOE
			case I40E_VSI_FCOE:
				qcount = num_tc_qps;
				break;
#endif
			case I40E_VSI_FDIR:
			case I40E_VSI_SRIOV:
			case I40E_VSI_VMDQ2:
			default:
				qcount = num_tc_qps;
				WARN_ON(i != 0);
				break;
			}
