if ((target_mask == (1 << tmp->device->id)) && (lun == tmp->device->lun)
#ifdef SUPPORT_TAGS
	    && (tag == tmp->tag) 
#endif
	    ) {
	    if (prev) {
		REMOVE(prev, NEXT(prev), tmp, NEXT(tmp));
		NEXT(prev) = NEXT(tmp);
	    } else {
		REMOVE(-1, hostdata->disconnected_queue, tmp, NEXT(tmp));
		hostdata->disconnected_queue = NEXT(tmp);
	    }
	    NEXT(tmp) = NULL;
	    break;
	}
