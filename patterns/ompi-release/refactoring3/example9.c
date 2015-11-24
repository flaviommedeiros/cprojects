switch (info->si_code)
            {
#ifdef FPE_INTDIV
            case FPE_INTDIV: si_code_str = "Integer divide-by-zero"; break;
#endif
#ifdef FPE_INTOVF
            case FPE_INTOVF: si_code_str = "Integer overflow"; break;
#endif
            case FPE_FLTDIV: si_code_str = "Floating point divide-by-zero"; break;
            case FPE_FLTOVF: si_code_str = "Floating point overflow"; break;
            case FPE_FLTUND: si_code_str = "Floating point underflow"; break;
#ifdef FPE_FLTRES
            case FPE_FLTRES: si_code_str = "Floating point inexact result"; break;
#endif
#ifdef FPE_FLTINV
            case FPE_FLTINV: si_code_str = "Invalid floating point operation"; break;
#endif
#ifdef FPE_FLTSUB
            case FPE_FLTSUB: si_code_str = "Subscript out of range"; break;
#endif
            }
