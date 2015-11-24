switch (clock_source) {
        case SYSTEM_CLOCK_SOURCE_OSC8M:
                    SYSCTRL->OSC8M.reg &= ~SYSCTRL_OSC8M_ENABLE;
                break;

            case SYSTEM_CLOCK_SOURCE_OSC32K:
                SYSCTRL->OSC32K.reg &= ~SYSCTRL_OSC32K_ENABLE;
                break;

            case SYSTEM_CLOCK_SOURCE_XOSC:
                SYSCTRL->XOSC.reg &= ~SYSCTRL_XOSC_ENABLE;
                break;

            case SYSTEM_CLOCK_SOURCE_XOSC32K:
                SYSCTRL->XOSC32K.reg &= ~SYSCTRL_XOSC32K_ENABLE;
                break;

            case SYSTEM_CLOCK_SOURCE_DFLL:
                _system_clock_inst.dfll.control &= ~SYSCTRL_DFLLCTRL_ENABLE;
                SYSCTRL->DFLLCTRL.reg = _system_clock_inst.dfll.control;
                break;

#ifdef FEATURE_SYSTEM_CLOCK_DPLL
            case SYSTEM_CLOCK_SOURCE_DPLL:
                SYSCTRL->DPLLCTRLA.reg &= ~SYSCTRL_DPLLCTRLA_ENABLE;
                break;
#endif

            case SYSTEM_CLOCK_SOURCE_ULP32K:
            /* Not possible to disable */

            default:
                Assert(false);
                return STATUS_ERR_INVALID_ARG;

        
