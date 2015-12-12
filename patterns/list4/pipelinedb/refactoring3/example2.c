switch (errcode)
	{
		case EAI_NONAME:
			return "Unknown host";
		case EAI_AGAIN:
			return "Host name lookup failure";
			/* Errors below are probably WIN32 only */
#ifdef EAI_BADFLAGS
		case EAI_BADFLAGS:
			return "Invalid argument";
#endif
#ifdef EAI_FAMILY
		case EAI_FAMILY:
			return "Address family not supported";
#endif
#ifdef EAI_MEMORY
		case EAI_MEMORY:
			return "Not enough memory";
#endif
#if defined(EAI_NODATA) && EAI_NODATA != EAI_NONAME		/* MSVC/WIN64 duplicate */
		case EAI_NODATA:
			return "No host data of that type was found";
#endif
#ifdef EAI_SERVICE
		case EAI_SERVICE:
			return "Class type not found";
#endif
#ifdef EAI_SOCKTYPE
		case EAI_SOCKTYPE:
			return "Socket type not supported";
#endif
		default:
			return "Unknown server error";
	}
