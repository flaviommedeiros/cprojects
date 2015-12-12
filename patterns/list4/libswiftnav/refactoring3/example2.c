switch((int)type)
		{
		case TYINT1:
		case TYSHORT:
		case TYLONG:
#ifndef ALLOW_FLOAT_IN_INTEGER_LIST_INPUT
			ERR(l_R(0,1));
			break;
#endif
		case TYREAL:
		case TYDREAL:
			ERR(l_R(0,0));
			break;
#ifdef TYQUAD
		case TYQUAD:
			n = l_R(0,2);
			if (n)
				return n;
			break;
#endif
		case TYCOMPLEX:
		case TYDCOMPLEX:
			ERR(l_C());
			break;
		case TYLOGICAL1:
		case TYLOGICAL2:
		case TYLOGICAL:
			ERR(l_L());
			break;
		case TYCHAR:
			ERR(l_CHAR());
			break;
		}
