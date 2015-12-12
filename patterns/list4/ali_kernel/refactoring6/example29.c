if ((target_mask == (1 << tmp->device->id)) && (lun == tmp->device->lun)
#ifdef SUPPORT_TAGS
		    && (tag == tmp->tag)
#endif
		    ) {
			/* ++guenther: prevent race with falcon_release_lock */
			falcon_dont_release++;
			if (prev) {
				REMOVE(prev, NEXT(prev), tmp, NEXT(tmp));
				SET_NEXT(prev, NEXT(tmp));
			} else {
				REMOVE(-1, hostdata->disconnected_queue, tmp, NEXT(tmp));
				hostdata->disconnected_queue = NEXT(tmp);
			}
			SET_NEXT(tmp, NULL);
			break;
		}
