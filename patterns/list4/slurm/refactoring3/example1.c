switch(cnodes) {
#ifdef HAVE_BGL
		case 32:
			blockreq.small32 = 4;
			blockreq.small128 = 3;
			break;
		case 128:
			blockreq.small128 = 4;
			break;
#else
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
#endif
		default:
			debug("This size %d is unknown on this system", cnodes);
			goto finished;
			break;
		}
