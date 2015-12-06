switch (clock_source) {
        case SYSTEM_CLOCK_SOURCE_OSC8M:
            mask = SYSCTRL_PCLKSR_OSC8MRDY;
            break;

        case SYSTEM_CLOCK_SOURCE_OSC32K:
            mask = SYSCTRL_PCLKSR_OSC32KRDY;
            break;

        case SYSTEM_CLOCK_SOURCE_XOSC:
            mask = SYSCTRL_PCLKSR_XOSCRDY;
            break;

        case SYSTEM_CLOCK_SOURCE_XOSC32K:
            mask = SYSCTRL_PCLKSR_XOSC32KRDY;
            break;

        case SYSTEM_CLOCK_SOURCE_DFLL:
            if (CONF_CLOCK_DFLL_LOOP_MODE == SYSTEM_CLOCK_DFLL_LOOP_MODE_CLOSED) {
                mask = (SYSCTRL_PCLKSR_DFLLRDY |
                        SYSCTRL_PCLKSR_DFLLLCKF | SYSCTRL_PCLKSR_DFLLLCKC);
            } else {
                mask = SYSCTRL_PCLKSR_DFLLRDY;
            }
            break;

#ifdef FEATURE_SYSTEM_CLOCK_DPLL
        case SYSTEM_CLOCK_SOURCE_DPLL:
            return ((SYSCTRL->DPLLSTATUS.reg &
                     (SYSCTRL_DPLLSTATUS_CLKRDY | SYSCTRL_DPLLSTATUS_LOCK)) ==
                    (SYSCTRL_DPLLSTATUS_CLKRDY | SYSCTRL_DPLLSTATUS_LOCK));
#endif

        case SYSTEM_CLOCK_SOURCE_ULP32K:
            /* Not possible to disable */
            return true;

        default:
            return false;
    }
