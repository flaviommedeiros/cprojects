switch (info->si_code)
            {
#ifdef ILL_ILLOPC
            case ILL_ILLOPC: si_code_str = "Illegal opcode"; break;
#endif
#ifdef ILL_ILLOPN
            case ILL_ILLOPN: si_code_str = "Illegal operand"; break;
#endif
#ifdef ILL_ILLADR
            case ILL_ILLADR: si_code_str = "Illegal addressing mode"; break;
#endif
#ifdef ILL_ILLTRP
            case ILL_ILLTRP: si_code_str = "Illegal trap"; break;
#endif
#ifdef ILL_PRVOPC
            case ILL_PRVOPC: si_code_str = "Privileged opcode"; break;
#endif
#ifdef ILL_PRVREG
            case ILL_PRVREG: si_code_str = "Privileged register"; break;
#endif
#ifdef ILL_COPROC
            case ILL_COPROC: si_code_str = "Coprocessor error"; break;
#endif
#ifdef ILL_BADSTK
            case ILL_BADSTK: si_code_str = "Internal stack error"; break;
#endif
            }
