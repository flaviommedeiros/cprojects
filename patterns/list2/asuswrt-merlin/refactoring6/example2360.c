if (
			#if 1
				*flags_p != MSG_HIPRI &&
			#endif
				((filp->f_op->poll(filp, wait) & POLLIN) ||
				(filp->f_op->poll(filp, NULL) & POLLIN) ||
				signal_pending(current))
			) {
				break;
			}
