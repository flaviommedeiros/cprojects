switch (c = GetKeyUpdate ()) {

            case  '+':
                StackAddr += BytesPerPage;
                break;

            case '-':
                StackAddr -= BytesPerPage;
                break;

            case 'o':
                StackHome ();
                break;

            case 'a':
#ifdef CH_CURS_UP:
            case CH_CURS_UP:
#endif
                --StackAddr;
                break;

            case 'z':
#ifdef CH_CURS_DOWN
            case CH_CURS_DOWN:
#endif
                ++StackAddr;
                break;

            default:
                return c;

        }
