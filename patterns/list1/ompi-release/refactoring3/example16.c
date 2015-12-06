switch (info->si_code)
            {
#ifdef BUS_ADRALN
            case BUS_ADRALN: si_code_str = "Invalid address alignment"; break;
#endif
#ifdef BUS_ADRERR
            case BUS_ADRERR: si_code_str = "Non-existant physical address"; break;
#endif
#ifdef BUS_OBJERR
            case BUS_OBJERR: si_code_str = "Objet-specific hardware error"; break;
#endif
            }
