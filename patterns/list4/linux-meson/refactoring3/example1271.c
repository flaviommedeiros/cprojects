switch (s->type) {
#ifdef XZ_DEC_X86
	case BCJ_X86:
		filtered = bcj_x86(s, buf, size);
		break;
#endif
#ifdef XZ_DEC_POWERPC
	case BCJ_POWERPC:
		filtered = bcj_powerpc(s, buf, size);
		break;
#endif
#ifdef XZ_DEC_IA64
	case BCJ_IA64:
		filtered = bcj_ia64(s, buf, size);
		break;
#endif
#ifdef XZ_DEC_ARM
	case BCJ_ARM:
		filtered = bcj_arm(s, buf, size);
		break;
#endif
#ifdef XZ_DEC_ARMTHUMB
	case BCJ_ARMTHUMB:
		filtered = bcj_armthumb(s, buf, size);
		break;
#endif
#ifdef XZ_DEC_SPARC
	case BCJ_SPARC:
		filtered = bcj_sparc(s, buf, size);
		break;
#endif
	default:
		/* Never reached but silence compiler warnings. */
		filtered = 0;
		break;
	}
