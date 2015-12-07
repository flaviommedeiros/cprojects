#ifndef FEATURE_MDDI_DISABLE_REVERSE
if ((pmhctl->rev_state != MDDI_REV_ENCAP_ISSUED) &&
	    (pmhctl->rev_state != MDDI_REV_STATUS_REQ_ISSUED))
#endif
		/* don't want simultaneous reverse and forward with Eagle */
		mddi_queue_forward_linked_list();
