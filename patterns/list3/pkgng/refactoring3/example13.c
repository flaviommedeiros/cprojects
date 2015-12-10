switch (*s) {
    case T('&'):
      fputts(T("&amp;"), fp);
      break;
    case T('<'):
      fputts(T("&lt;"), fp);
      break;
    case T('>'):
      fputts(T("&gt;"), fp);
      break;
#ifdef W3C14N
    case 13:
      fputts(T("&#xD;"), fp);
      break;
#else
    case T('"'):
      fputts(T("&quot;"), fp);
      break;
    case 9:
    case 10:
    case 13:
      ftprintf(fp, T("&#%d;"), *s);
      break;
#endif
    default:
      puttc(*s, fp);
      break;
    }
