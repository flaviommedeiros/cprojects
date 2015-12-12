switch(bg_record->cnode_cnt) {
#ifdef HAVE_BGL
	case 32:
		error("We got a 32 we should never have this");
		goto finished;
		break;
	case 128:
		switch(cnodes) {
		case 32:
			blockreq.small32 = 4;
			break;
		default:
			error("We don't make a %d from size %d",
			      cnodes, bg_record->cnode_cnt);
			goto finished;
			break;
		}
		break;
	default:
		switch(cnodes) {
		case 32:
			blockreq.small32 = 4;
			blockreq.small128 = 3;
			break;
		case 128:
			blockreq.small128 = 4;
			break;
		default:
			error("We don't make a %d from size %d",
			      cnodes, bg_record->cnode_cnt);
			goto finished;
			break;
		}
		full_mp = true;
		break;
#else
	case 16:
		error("We got a 16 we should never have this");
		goto finished;
		break;
	case 32:
		switch(cnodes) {
		case 16:
			blockreq.small16 = 2;
			break;
		default:
			error("We don't make a %d from size %d",
			      cnodes, bg_record->cnode_cnt);
			goto finished;
			break;
		}
		break;
	case 64:
		switch(cnodes) {
		case 16:
			blockreq.small16 = 2;
			blockreq.small32 = 1;
			break;
		case 32:
			blockreq.small32 = 2;
			break;
		default:
			error("We don't make a %d from size %d",
			      cnodes, bg_record->cnode_cnt);
			goto finished;
			break;
		}
		break;
	case 128:
		switch(cnodes) {
		case 16:
			blockreq.small16 = 2;
			blockreq.small32 = 1;
			blockreq.small64 = 1;
			break;
		case 32:
			blockreq.small32 = 2;
			blockreq.small64 = 1;
			break;
		case 64:
			blockreq.small64 = 2;
			break;
		default:
			error("We don't make a %d from size %d",
			      cnodes, bg_record->cnode_cnt);
			goto finished;
			break;
		}
		break;
	case 256:
		switch(cnodes) {
		case 16:
			blockreq.small16 = 2;
			blockreq.small32 = 1;
			blockreq.small64 = 1;
			blockreq.small128 = 1;
			break;
		case 32:
			blockreq.small32 = 2;
			blockreq.small64 = 1;
			blockreq.small128 = 1;
			break;
		case 64:
			blockreq.small64 = 2;
			blockreq.small128 = 1;
			break;
		case 128:
			blockreq.small128 = 2;
			break;
		default:
			error("We don't make a %d from size %d",
			      cnodes, bg_record->cnode_cnt);
			goto finished;
			break;
		}
		break;
	default:
		switch(cnodes) {
		case 16:
			blockreq.small16 = 2;
			blockreq.small32 = 1;
			blockreq.small64 = 1;
			blockreq.small128 = 1;
			blockreq.small256 = 1;
			break;
		case 32:
			blockreq.small32 = 2;
			blockreq.small64 = 1;
			blockreq.small128 = 1;
			blockreq.small256 = 1;
			break;
		case 64:
			blockreq.small64 = 2;
			blockreq.small128 = 1;
			blockreq.small256 = 1;
			break;
		case 128:
			blockreq.small128 = 2;
			blockreq.small256 = 1;
			break;
		case 256:
			blockreq.small256 = 2;
			break;
		default:
			error("We don't make a %d from size %d",
			      cnodes, bg_record->cnode_cnt);
			goto finished;
			break;
		}
		full_mp = true;
		break;
#endif
	}
