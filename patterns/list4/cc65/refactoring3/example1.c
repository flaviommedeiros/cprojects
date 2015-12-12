switch (c = GetKeyUpdate ()) {

            case  '+':
                AsmAddr = Last;
                break;

            case '-':
                AsmAddr = AsmBack (AsmAddr, AsmFrame.fd_height);
                break;

            case 't':
#ifdef CH_F2
            case CH_F2:
#endif
                DbgToggleUserBreak (AsmAddr);
                break;

            case 'f':
                AsmFollow ();
                break;

            case 'g':
                InputGoto (&AsmAddr);
                break;

            case 'o':
                AsmHome ();
                break;

            case 'p':
                brk_pc = AsmAddr;
                break;

            case 'a':
#ifdef CH_CURS_UP
            case CH_CURS_UP:
#endif
                AsmAddr = AsmBack (AsmAddr, 1);
                break;

            case 'z':
#ifdef CH_CURS_DOWN
            case CH_CURS_DOWN:
#endif
                AsmAddr += DbgDisAsmLen (AsmAddr);
                break;

            default:
                return c;

        }
