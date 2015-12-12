switch (tsb_idx) {
		case MM_TSB_BASE:
			hp->pgsz_mask = HV_PGSZ_MASK_BASE;
			break;
#ifdef CONFIG_HUGETLB_PAGE
		case MM_TSB_HUGE:
			hp->pgsz_mask = HV_PGSZ_MASK_HUGE;
			break;
#endif
		default:
			BUG();
		}
