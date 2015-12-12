switch (code) {
#ifdef SLEEP_LED_ENABLE
        case KC_Z:
            // test breathing sleep LED
            print("Sleep LED test\n");
            sleep_led_toggle();
            led_set(host_keyboard_leds());
            break;
#endif
#ifdef BOOTMAGIC_ENABLE
        case KC_E:
            print("eeconfig:\n");
            print_eeconfig();
            break;
#endif
#ifdef KEYBOARD_LOCK_ENABLE
        case KC_CAPSLOCK:
            if (host_get_driver()) {
                host_driver = host_get_driver();
                clear_keyboard();
                host_set_driver(0);
                print("Locked.\n");
            } else {
                host_set_driver(host_driver);
                print("Unlocked.\n");
            }
            break;
#endif
        case KC_H:
        case KC_SLASH: /* ? */
            command_common_help();
            break;
        case KC_C:
            debug_matrix   = false;
            debug_keyboard = false;
            debug_mouse    = false;
            debug_enable   = false;
            command_console_help();
            print("C> ");
            command_state = CONSOLE;
            break;
        case KC_PAUSE:
            clear_keyboard();
            print("\n\nbootloader... ");
            _delay_ms(1000);
            bootloader_jump(); // not return
            break;
        case KC_D:
            if (debug_enable) {
                print("\ndebug: off\n");
                debug_matrix   = false;
                debug_keyboard = false;
                debug_mouse    = false;
                debug_enable   = false;
            } else {
                print("\ndebug: on\n");
                debug_enable   = true;
            }
            break;
        case KC_X: // debug matrix toggle
            debug_matrix = !debug_matrix;
            if (debug_matrix) {
                print("\nmatrix: on\n");
                debug_enable = true;
            } else {
                print("\nmatrix: off\n");
            }
            break;
        case KC_K: // debug keyboard toggle
            debug_keyboard = !debug_keyboard;
            if (debug_keyboard) {
                print("\nkeyboard: on\n");
                debug_enable = true;
            } else {
                print("\nkeyboard: off\n");
            }
            break;
        case KC_M: // debug mouse toggle
            debug_mouse = !debug_mouse;
            if (debug_mouse) {
                print("\nmouse: on\n");
                debug_enable = true;
            } else {
                print("\nmouse: off\n");
            }
            break;
        case KC_V: // print version & information
            print("\n\t- Version -\n");
            print("DESC: " STR(DESCRIPTION) "\n");
            print("VID: " STR(VENDOR_ID) "(" STR(MANUFACTURER) ") "
                  "PID: " STR(PRODUCT_ID) "(" STR(PRODUCT) ") "
                  "VER: " STR(DEVICE_VER) "\n");
            print("BUILD: " STR(VERSION) " (" __TIME__ " " __DATE__ ")\n");
            /* build options */
            print("OPTIONS:"
#ifdef PROTOCOL_PJRC
            " PJRC"
#endif
#ifdef PROTOCOL_LUFA
            " LUFA"
#endif
#ifdef PROTOCOL_VUSB
            " VUSB"
#endif
#ifdef BOOTMAGIC_ENABLE
            " BOOTMAGIC"
#endif
#ifdef MOUSEKEY_ENABLE
            " MOUSEKEY"
#endif
#ifdef EXTRAKEY_ENABLE
            " EXTRAKEY"
#endif
#ifdef CONSOLE_ENABLE
            " CONSOLE"
#endif
#ifdef COMMAND_ENABLE
            " COMMAND"
#endif
#ifdef NKRO_ENABLE
            " NKRO"
#endif
#ifdef KEYMAP_SECTION_ENABLE
            " KEYMAP_SECTION"
#endif
            " " STR(BOOTLOADER_SIZE) "\n");

            print("GCC: " STR(__GNUC__) "." STR(__GNUC_MINOR__) "." STR(__GNUC_PATCHLEVEL__)
                  " AVR-LIBC: " __AVR_LIBC_VERSION_STRING__
                  " AVR_ARCH: avr" STR(__AVR_ARCH__) "\n");
            break;
        case KC_S:
            print("\n\t- Status -\n");
            print_val_hex8(host_keyboard_leds());
            print_val_hex8(keyboard_protocol);
            print_val_hex8(keyboard_idle);
#ifdef NKRO_ENABLE
            print_val_hex8(keyboard_nkro);
#endif
            print_val_hex32(timer_count);

#ifdef PROTOCOL_PJRC
            print_val_hex8(UDCON);
            print_val_hex8(UDIEN);
            print_val_hex8(UDINT);
            print_val_hex8(usb_keyboard_leds);
            print_val_hex8(usb_keyboard_idle_count);
#endif

#ifdef PROTOCOL_PJRC
#   if USB_COUNT_SOF
            print_val_hex8(usbSofCount);
#   endif
#endif
            break;
#ifdef NKRO_ENABLE
        case KC_N:
            clear_keyboard(); //Prevents stuck keys.
            keyboard_nkro = !keyboard_nkro;
            if (keyboard_nkro)
                print("NKRO: on\n");
            else
                print("NKRO: off\n");
            break;
#endif
        case KC_ESC:
        case KC_GRV:
        case KC_0:
        case KC_F10:
            switch_default_layer(0);
            break;
        case KC_1 ... KC_9:
            switch_default_layer((code - KC_1) + 1);
            break;
        case KC_F1 ... KC_F9:
            switch_default_layer((code - KC_F1) + 1);
            break;
        default:
            print("?");
            return false;
    }
