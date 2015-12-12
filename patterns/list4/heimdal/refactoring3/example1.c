switch(eai_errno) {
    case EAI_NOERROR:
	return 0;
#ifdef EAI_ADDRFAMILY
    case EAI_ADDRFAMILY:
	return HEIM_EAI_ADDRFAMILY;
#endif
    case EAI_AGAIN:
	return HEIM_EAI_AGAIN;
    case EAI_BADFLAGS:
	return HEIM_EAI_BADFLAGS;
    case EAI_FAIL:
	return HEIM_EAI_FAIL;
    case EAI_FAMILY:
	return HEIM_EAI_FAMILY;
    case EAI_MEMORY:
	return HEIM_EAI_MEMORY;
#if defined(EAI_NODATA) && EAI_NODATA != EAI_NONAME
    case EAI_NODATA:
	return HEIM_EAI_NODATA;
#endif
#ifdef WSANO_DATA
    case WSANO_DATA:
	return HEIM_EAI_NODATA;
#endif
    case EAI_NONAME:
	return HEIM_EAI_NONAME;
    case EAI_SERVICE:
	return HEIM_EAI_SERVICE;
    case EAI_SOCKTYPE:
	return HEIM_EAI_SOCKTYPE;
#ifdef EAI_SYSTEM
    case EAI_SYSTEM:
	return system_error;
#endif
    default:
	return HEIM_EAI_UNKNOWN; /* XXX */
    }
