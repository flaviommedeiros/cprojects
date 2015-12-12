switch(sym->sym)
    {
        case SDLK_LEFT:        return KEY_LEFTARROW;
        case SDLK_RIGHT:       return KEY_RIGHTARROW;
        case SDLK_DOWN:        return KEY_DOWNARROW;
        case SDLK_UP:          return KEY_UPARROW;
        case SDLK_ESCAPE:      return KEY_ESCAPE;
        case SDLK_RETURN:      return KEY_ENTER;
        case SDLK_TAB:         return KEY_TAB;
        case SDLK_F1:          return KEY_F1;
        case SDLK_F2:          return KEY_F2;
        case SDLK_F3:          return KEY_F3;
        case SDLK_F4:          return KEY_F4;
        case SDLK_F5:          return KEY_F5;
        case SDLK_F6:          return KEY_F6;
        case SDLK_F7:          return KEY_F7;
        case SDLK_F8:          return KEY_F8;
        case SDLK_F9:          return KEY_F9;
        case SDLK_F10:         return KEY_F10;
        case SDLK_F11:         return KEY_F11;
        case SDLK_F12:         return KEY_F12;
        case SDLK_PRINT:       return KEY_PRTSCR;

        case SDLK_BACKSPACE:   return KEY_BACKSPACE;
        case SDLK_DELETE:      return KEY_DEL;

        case SDLK_PAUSE:       return KEY_PAUSE;

        case SDLK_LSHIFT:
        case SDLK_RSHIFT:
                               return KEY_RSHIFT;

        case SDLK_LCTRL:
        case SDLK_RCTRL:
                               return KEY_RCTRL;

        case SDLK_LALT:
        case SDLK_RALT:
        case SDLK_LMETA:
        case SDLK_RMETA:
                               return KEY_RALT;

        case SDLK_CAPSLOCK:    return KEY_CAPSLOCK;
        case SDLK_SCROLLOCK:   return KEY_SCRLCK;

        case SDLK_HOME:        return KEY_HOME;
        case SDLK_INSERT:      return KEY_INS;
        case SDLK_END:         return KEY_END;
        case SDLK_PAGEUP:      return KEY_PGUP;
        case SDLK_PAGEDOWN:    return KEY_PGDN;

#ifdef SDL_HAVE_APP_KEYS
        case SDLK_APP1:        return KEY_F1;
        case SDLK_APP2:        return KEY_F2;
        case SDLK_APP3:        return KEY_F3;
        case SDLK_APP4:        return KEY_F4;
        case SDLK_APP5:        return KEY_F5;
        case SDLK_APP6:        return KEY_F6;
#endif

        default:               break;
    }
