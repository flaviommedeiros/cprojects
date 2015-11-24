switch (info->si_code)
            {
#ifdef TRAP_BRKPT
            case TRAP_BRKPT: si_code_str = "Process breakpoint"; break;
#endif
#ifdef TRAP_TRACE
            case TRAP_TRACE: si_code_str = "Process trace trap"; break;
#endif
            }
