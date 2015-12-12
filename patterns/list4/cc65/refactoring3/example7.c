switch (c = GetKeyUpdate ()) {

            case  '+':
                DumpAddr += BytesPerPage;
                break;

            case '-':
                DumpAddr -= BytesPerPage;
                break;

            case 'g':
                InputGoto (&DumpAddr);
                break;

            case 'o':
                DumpHome ();
                break;

            case 'a':
#ifdef CH_CURS_UP
            case CH_CURS_UP:
#endif
                DumpAddr -= 8;
                break;

            case 'z':
#ifdef CH_CURS_DOWN
            case CH_CURS_DOWN:
#endif
                DumpAddr += 8;
                break;

            default:
                return c;

        }
