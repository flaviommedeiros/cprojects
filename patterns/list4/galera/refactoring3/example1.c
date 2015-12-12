switch (*scan++) {
	case 'd':
	    _gu_db_on_ = TRUE;
	    _gu_db_stack->flags |= DEBUG_ON;
	    if (*scan++ == ',') {
		_gu_db_stack->keywords = ListParse(scan);
	    }
	    break;
	case 'D':
	    _gu_db_stack->delay = 0;
	    if (*scan++ == ',') {
		temp = ListParse(scan);
		_gu_db_stack->delay = DelayArg(atoi(temp->str));
		FreeList(temp);
	    }
	    break;
	case 'f':
	    if (*scan++ == ',') {
		_gu_db_stack->functions = ListParse(scan);
	    }
	    break;
	case 'F':
	    _gu_db_stack->flags |= FILE_ON;
	    break;
	case 'i':
	    _gu_db_stack->flags |= PID_ON;
	    break;
#ifndef THREAD
	case 'g':
	    _gu_db_pon_ = TRUE;
	    if (OpenProfile(PROF_FILE)) {
		_gu_db_stack->flags |= PROFILE_ON;
		if (*scan++ == ',')
		    _gu_db_stack->p_functions = ListParse(scan);
	    }
	    break;
#endif
	case 'L':
	    _gu_db_stack->flags |= LINE_ON;
	    break;
	case 'n':
	    _gu_db_stack->flags |= DEPTH_ON;
	    break;
	case 'N':
	    _gu_db_stack->flags |= NUMBER_ON;
	    break;
	case 'A':
	case 'O':
	    _gu_db_stack->flags |= FLUSH_ON_WRITE;
	case 'a':
	case 'o':
	    if (*scan++ == ',') {
		temp = ListParse(scan);
		GU_DBUGOpenFile(temp->str, (int) (scan[-2] == 'A'
			|| scan[-2] == 'a'));
		FreeList(temp);
	    } else {
		GU_DBUGOpenFile("-", 0);
	    }
	    break;
	case 'p':
	    if (*scan++ == ',') {
		_gu_db_stack->processes = ListParse(scan);
	    }
	    break;
	case 'P':
	    _gu_db_stack->flags |= PROCESS_ON;
	    break;
	case 'r':
	    _gu_db_stack->sub_level = state->level;
	    break;
	case 't':
	    _gu_db_stack->flags |= TRACE_ON;
	    if (*scan++ == ',') {
		temp = ListParse(scan);
		_gu_db_stack->maxdepth = atoi(temp->str);
		FreeList(temp);
	    }
	    break;
	case 'S':
	    _gu_db_stack->flags |= SANITY_CHECK_ON;
	    break;
	}
