#ifdef USE_RBPS
if (RBRQ_ADDR(he_dev->rbrq_head) & RBP_SMALLBUF)
			rbp = &he_dev->rbps_base[RBP_INDEX(RBRQ_ADDR(he_dev->rbrq_head))];
		else
#endif
			rbp = &he_dev->rbpl_base[RBP_INDEX(RBRQ_ADDR(he_dev->rbrq_head))];
