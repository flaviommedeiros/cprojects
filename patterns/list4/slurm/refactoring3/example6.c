switch(smallest_bg_record->cnode_cnt) {
#ifndef HAVE_BGL
		case 64:
			blockreq.small32 = 2;
			break;
		case 256:
			blockreq.small32 = 8;
			break;
#endif
		case 128:
			blockreq.small32 = 4;
			break;
		case 512:
		default:
			blockreq.small32 = 16;
			break;
		}
