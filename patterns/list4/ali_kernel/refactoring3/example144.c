switch (pa->p_type) {
	case SMT_P10F0 :
	case SMT_P10F1 :
#ifdef	ESS
	case SMT_P10F2 :
	case SMT_P10F3 :
	case SMT_P10F4 :
	case SMT_P10F5 :
	case SMT_P10F6 :
	case SMT_P10F7 :
#endif
#ifdef	SBA
	case SMT_P10F8 :
	case SMT_P10F9 :
#endif
	case SMT_P20F1 :
		if (!local) {
			return(SMT_RDF_NOPARAM) ;
		}
		break ;
	}
