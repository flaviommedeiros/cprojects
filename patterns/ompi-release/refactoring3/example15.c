switch (info->si_code)
            {
#ifdef SEGV_MAPERR
            case SEGV_MAPERR: si_code_str = "Address not mapped"; break;
#endif
#ifdef SEGV_ACCERR
            case SEGV_ACCERR: si_code_str = "Invalid permissions"; break;
#endif
            }
