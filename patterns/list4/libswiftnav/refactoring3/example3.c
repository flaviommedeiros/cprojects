switch((int)type)
		{
		case TYINT1:
		case TYLOGICAL1:
			Ptr->flchar = (char)f__lx;
			break;
		case TYLOGICAL2:
		case TYSHORT:
			Ptr->flshort = (short)f__lx;
			break;
		case TYLOGICAL:
		case TYLONG:
			Ptr->flint = (ftnint)f__lx;
			break;
#ifdef Allow_TYQUAD
		case TYQUAD:
			if (!(Ptr->fllongint = f__llx))
				Ptr->fllongint = f__lx;
			break;
#endif
		case TYREAL:
			Ptr->flreal=f__lx;
			break;
		case TYDREAL:
			Ptr->fldouble=f__lx;
			break;
		case TYCOMPLEX:
			xx=(real *)ptr;
			*xx++ = f__lx;
			*xx = f__ly;
			break;
		case TYDCOMPLEX:
			yy=(doublereal *)ptr;
			*yy++ = f__lx;
			*yy = f__ly;
			break;
		case TYCHAR:
			b_char(f__lchar,ptr,len);
			break;
		}
