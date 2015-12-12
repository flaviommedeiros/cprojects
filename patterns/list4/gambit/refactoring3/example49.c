switch (ev->event_kind)
          {
#ifdef LINEEDITOR_SUPPORT_F5_TO_F12
          case LINEEDITOR_EV_F8:
            command[5] = ___UNICODE_LOWER_C;
            break;
          case LINEEDITOR_EV_F9:
            command[5] = ___UNICODE_MINUS;
            break;
          case LINEEDITOR_EV_F10:
            command[5] = ___UNICODE_PLUS;
            break;
          case LINEEDITOR_EV_F11:
            command[5] = ___UNICODE_LOWER_S;
            break;
          case LINEEDITOR_EV_F12:
            command[5] = ___UNICODE_LOWER_L;
            break;
#endif
          default:
            command[5] = ___UNICODE_LOWER_T;
            break;
          }
