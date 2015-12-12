switch (wIndex) {
            case KEYBOARD_INTERFACE:
                Address = &KeyboardReport;
                Size    = sizeof(KeyboardReport);
                break;
#ifdef MOUSE_ENABLE
            case MOUSE_INTERFACE:
                Address = &MouseReport;
                Size    = sizeof(MouseReport);
                break;
#endif
#ifdef EXTRAKEY_ENABLE
            case EXTRAKEY_INTERFACE:
                Address = &ExtrakeyReport;
                Size    = sizeof(ExtrakeyReport);
                break;
#endif
#ifdef CONSOLE_ENABLE
            case CONSOLE_INTERFACE:
                Address = &ConsoleReport;
                Size    = sizeof(ConsoleReport);
                break;
#endif
#ifdef NKRO_ENABLE
            case NKRO_INTERFACE:
                Address = &NKROReport;
                Size    = sizeof(NKROReport);
                break;
#endif
            }
