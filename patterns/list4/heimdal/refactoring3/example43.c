switch (i) {
#ifdef VINTR
	case C_INTR:
		return VINTR;
#endif /* VINTR */
#ifdef VQUIT
	case C_QUIT:
		return VQUIT;
#endif /* VQUIT */
#ifdef VERASE
	case C_ERASE:
		return VERASE;
#endif /* VERASE */
#ifdef VKILL
	case C_KILL:
		return VKILL;
#endif /* VKILL */
#ifdef VEOF
	case C_EOF:
		return VEOF;
#endif /* VEOF */
#ifdef VEOL
	case C_EOL:
		return VEOL;
#endif /* VEOL */
#ifdef VEOL2
	case C_EOL2:
		return VEOL2;
#endif /* VEOL2 */
#ifdef VSWTCH
	case C_SWTCH:
		return VSWTCH;
#endif /* VSWTCH */
#ifdef VDSWTCH
	case C_DSWTCH:
		return VDSWTCH;
#endif /* VDSWTCH */
#ifdef VERASE2
	case C_ERASE2:
		return VERASE2;
#endif /* VERASE2 */
#ifdef VSTART
	case C_START:
		return VSTART;
#endif /* VSTART */
#ifdef VSTOP
	case C_STOP:
		return VSTOP;
#endif /* VSTOP */
#ifdef VWERASE
	case C_WERASE:
		return VWERASE;
#endif /* VWERASE */
#ifdef VSUSP
	case C_SUSP:
		return VSUSP;
#endif /* VSUSP */
#ifdef VDSUSP
	case C_DSUSP:
		return VDSUSP;
#endif /* VDSUSP */
#ifdef VREPRINT
	case C_REPRINT:
		return VREPRINT;
#endif /* VREPRINT */
#ifdef VDISCARD
	case C_DISCARD:
		return VDISCARD;
#endif /* VDISCARD */
#ifdef VLNEXT
	case C_LNEXT:
		return VLNEXT;
#endif /* VLNEXT */
#ifdef VSTATUS
	case C_STATUS:
		return VSTATUS;
#endif /* VSTATUS */
#ifdef VPAGE
	case C_PAGE:
		return VPAGE;
#endif /* VPAGE */
#ifdef VPGOFF
	case C_PGOFF:
		return VPGOFF;
#endif /* VPGOFF */
#ifdef VKILL2
	case C_KILL2:
		return VKILL2;
#endif /* KILL2 */
#ifdef VMIN
	case C_MIN:
		return VMIN;
#endif /* VMIN */
#ifdef VTIME
	case C_TIME:
		return VTIME;
#endif /* VTIME */
	default:
		return -1;
	}
