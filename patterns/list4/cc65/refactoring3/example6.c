switch (c = GetKeyUpdate ()) {

            case  '+':
                CStackAddr += BytesPerPage;
                break;

            case '-':
                CStackAddr -= BytesPerPage;
                break;

            case 'o':
                CStackHome ();
                break;

            case 'a':
#ifdef CH_CURS_UP
            case CH_CURS_UP:
#endif
                CStackAddr -= 2;
                break;

            case 'z':
#ifdef CH_CURS_DOWN
            case CH_CURS_DOWN:
#endif
                CStackAddr += 2;
                break;

            default:
                return c;

        }
