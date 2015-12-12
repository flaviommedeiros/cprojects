switch (code) {
        case KC_H:
        case KC_SLASH: /* ? */
            command_console_help();
            break;
        case KC_Q:
        case KC_ESC:
            command_state = ONESHOT;
            return false;
#ifdef MOUSEKEY_ENABLE
        case KC_M:
            mousekey_console_help();
            print("M> ");
            command_state = MOUSEKEY;
            return true;
#endif
        default:
            print("?");
            return false;
    }
