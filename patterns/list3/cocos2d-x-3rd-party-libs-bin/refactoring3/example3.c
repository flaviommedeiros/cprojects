switch (err) {
        case EAI_AGAIN: return "temporary failure in name resolution";
        case EAI_BADFLAGS: return "invalid value for ai_flags";
#ifdef EAI_BADHINTS
        case EAI_BADHINTS: return "invalid value for hints";
#endif
        case EAI_FAIL: return "non-recoverable failure in name resolution";
        case EAI_FAMILY: return "ai_family not supported";
        case EAI_MEMORY: return "memory allocation failure";
        case EAI_NONAME: 
            return "host or service not provided, or not known";
#ifdef EAI_OVERFLOW
        case EAI_OVERFLOW: return "argument buffer overflow";
#endif
#ifdef EAI_PROTOCOL
        case EAI_PROTOCOL: return "resolved protocol is unknown";
#endif
        case EAI_SERVICE: return "service not supported for socket type";
        case EAI_SOCKTYPE: return "ai_socktype not supported";
#ifdef EAI_SYSTEM
        case EAI_SYSTEM: return strerror(errno); 
#endif
        default: return gai_strerror(err);
    }
