switch (ret) {
#ifdef EAI_ADDRFAMILY
        case EAI_ADDRFAMILY:
#endif
        case EAI_NODATA:
            set_errno(ENOENT);
            break;
        case EAI_FAMILY:
            set_errno(EAFNOSUPPORT);
            break;
        case EAI_AGAIN:
            set_errno(EAGAIN);
            break;
#ifdef EAI_SYSTEM
        case EAI_SYSTEM:
            if (errno == EINTR)
                continue;
            break;
#endif
        default:
            set_errno(EINVAL);
        }
