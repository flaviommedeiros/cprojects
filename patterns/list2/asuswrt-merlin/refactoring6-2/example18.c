while (p->id < pin->id
#ifdef PID_SIMULATE_BACKTRACK
	     || (get_random() % 64) < 31
#endif
	     )
	{
	  CIRC_LIST_PUSH (p->seq_list, SEQ_UNSEEN);
	  ++p->id;
	}
