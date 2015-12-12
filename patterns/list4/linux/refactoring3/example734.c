switch (id) {
#ifdef XZ_DEC_X86
	case BCJ_X86:
#endif
#ifdef XZ_DEC_POWERPC
	case BCJ_POWERPC:
#endif
#ifdef XZ_DEC_IA64
	case BCJ_IA64:
#endif
#ifdef XZ_DEC_ARM
	case BCJ_ARM:
#endif
#ifdef XZ_DEC_ARMTHUMB
	case BCJ_ARMTHUMB:
#endif
#ifdef XZ_DEC_SPARC
	case BCJ_SPARC:
#endif
		break;

	default:
		/* Unsupported Filter ID */
		return XZ_OPTIONS_ERROR;
	
