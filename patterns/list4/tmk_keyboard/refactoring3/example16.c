switch (command_state) {
        case ONESHOT:
            if (!IS_COMMAND())
                return false;
            return (command_extra(code) || command_common(code));
            break;
        case CONSOLE:
            if (IS_COMMAND())
                return (command_extra(code) || command_common(code));
            else
                return (command_console_extra(code) || command_console(code));
            break;
#ifdef MOUSEKEY_ENABLE
        case MOUSEKEY:
            mousekey_console(code);
            break;
#endif
        default:
            command_state = ONESHOT;
            return false;
    }
