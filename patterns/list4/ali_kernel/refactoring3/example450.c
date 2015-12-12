switch (tsb_idx) {
		case MM_TSB_BASE:
			hp->pgsz_idx = HV_PGSZ_IDX_BASE;
			break;
#ifdef CONFIG_HUGETLB_PAGE
		case MM_TSB_HUGE:
			hp->pgsz_idx = HV_PGSZ_IDX_HUGE;
			break;
#endif
		default:
			BUG();
		}
