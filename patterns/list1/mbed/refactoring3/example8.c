switch (clock_source) {
        case SYSTEM_CLOCK_SOURCE_XOSC:
            return _system_clock_inst.xosc.frequency;

        case SYSTEM_CLOCK_SOURCE_OSC8M:
            return 8000000UL >> SYSCTRL->OSC8M.bit.PRESC;

        case SYSTEM_CLOCK_SOURCE_OSC32K:
            return 32768UL;

        case SYSTEM_CLOCK_SOURCE_ULP32K:
            return 32768UL;

        case SYSTEM_CLOCK_SOURCE_XOSC32K:
            return _system_clock_inst.xosc32k.frequency;

        case SYSTEM_CLOCK_SOURCE_DFLL:

            /* Check if the DFLL has been configured */
            if (!(_system_clock_inst.dfll.control & SYSCTRL_DFLLCTRL_ENABLE))
                return 0;

            /* Make sure that the DFLL module is ready */
            _system_dfll_wait_for_sync();

            /* Check if operating in closed loop mode */
            if (_system_clock_inst.dfll.control & SYSCTRL_DFLLCTRL_MODE) {
                return system_gclk_chan_get_hz(SYSCTRL_GCLK_ID_DFLL48) *
                       (_system_clock_inst.dfll.mul & 0xffff);
            }

            return 48000000UL;

#ifdef FEATURE_SYSTEM_CLOCK_DPLL
        case SYSTEM_CLOCK_SOURCE_DPLL:
            if (!(SYSCTRL->DPLLSTATUS.reg & SYSCTRL_DPLLSTATUS_ENABLE)) {
                return 0;
            }

            return _system_clock_inst.dpll.frequency;
#endif

        default:
            return 0;
    }
