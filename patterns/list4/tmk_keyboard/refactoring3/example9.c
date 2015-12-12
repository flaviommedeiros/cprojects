switch (action.kind.id) {
        /* Key and Mods */
        case ACT_LMODS:
        case ACT_RMODS:
            {
                uint8_t mods = (action.kind.id == ACT_LMODS) ?  action.key.mods :
                                                                action.key.mods<<4;
                if (event.pressed) {
                    if (mods) {
                        add_weak_mods(mods);
                        send_keyboard_report();
                    }
                    register_code(action.key.code);
                } else {
                    unregister_code(action.key.code);
                    if (mods) {
                        del_weak_mods(mods);
                        send_keyboard_report();
                    }
                }
            }
            break;
#ifndef NO_ACTION_TAPPING
        case ACT_LMODS_TAP:
        case ACT_RMODS_TAP:
            {
                uint8_t mods = (action.kind.id == ACT_LMODS_TAP) ?  action.key.mods :
                                                                    action.key.mods<<4;
                switch (action.layer_tap.code) {
    #ifndef NO_ACTION_ONESHOT
                    case MODS_ONESHOT:
                        // Oneshot modifier
                        if (event.pressed) {
                            if (tap_count == 0) {
                                register_mods(mods);
                            }
                            else if (tap_count == 1) {
                                dprint("MODS_TAP: Oneshot: start\n");
                                set_oneshot_mods(mods);
                            }
                            else {
                                register_mods(mods);
                            }
                        } else {
                            if (tap_count == 0) {
                                clear_oneshot_mods();
                                unregister_mods(mods);
                            }
                            else if (tap_count == 1) {
                                // Retain Oneshot mods
                            }
                            else {
                                clear_oneshot_mods();
                                unregister_mods(mods);
                            }
                        }
                        break;
    #endif
                    case MODS_TAP_TOGGLE:
                        if (event.pressed) {
                            if (tap_count <= TAPPING_TOGGLE) {
                                if (mods & get_mods()) {
                                    dprint("MODS_TAP_TOGGLE: toggle mods off\n");
                                    unregister_mods(mods);
                                } else {
                                    dprint("MODS_TAP_TOGGLE: toggle mods on\n");
                                    register_mods(mods);
                                }
                            }
                        } else {
                            if (tap_count < TAPPING_TOGGLE) {
                                dprint("MODS_TAP_TOGGLE: release : unregister_mods\n");
                                unregister_mods(mods);
                            }
                        }
                        break;
                    default:
                        if (event.pressed) {
                            if (tap_count > 0) {
                                if (record->tap.interrupted) {
                                    dprint("MODS_TAP: Tap: Cancel: add_mods\n");
                                    // ad hoc: set 0 to cancel tap
                                    record->tap.count = 0;
                                    register_mods(mods);
                                } else {
                                    dprint("MODS_TAP: Tap: register_code\n");
                                    register_code(action.key.code);
                                }
                            } else {
                                dprint("MODS_TAP: No tap: add_mods\n");
                                register_mods(mods);
                            }
                        } else {
                            if (tap_count > 0) {
                                dprint("MODS_TAP: Tap: unregister_code\n");
                                unregister_code(action.key.code);
                            } else {
                                dprint("MODS_TAP: No tap: add_mods\n");
                                unregister_mods(mods);
                            }
                        }
                        break;
                }
            }
            break;
#endif
#ifdef EXTRAKEY_ENABLE
        /* other HID usage */
        case ACT_USAGE:
            switch (action.usage.page) {
                case PAGE_SYSTEM:
                    if (event.pressed) {
                        host_system_send(action.usage.code);
                    } else {
                        host_system_send(0);
                    }
                    break;
                case PAGE_CONSUMER:
                    if (event.pressed) {
                        host_consumer_send(action.usage.code);
                    } else {
                        host_consumer_send(0);
                    }
                    break;
            }
            break;
#endif
#ifdef MOUSEKEY_ENABLE
        /* Mouse key */
        case ACT_MOUSEKEY:
            if (event.pressed) {
                mousekey_on(action.key.code);
                mousekey_send();
            } else {
                mousekey_off(action.key.code);
                mousekey_send();
            }
            break;
#endif
#ifndef NO_ACTION_LAYER
        case ACT_LAYER:
            if (action.layer_bitop.on == 0) {
                /* Default Layer Bitwise Operation */
                if (!event.pressed) {
                    uint8_t shift = action.layer_bitop.part*4;
                    uint32_t bits = ((uint32_t)action.layer_bitop.bits)<<shift;
                    uint32_t mask = (action.layer_bitop.xbit) ? ~(((uint32_t)0xf)<<shift) : 0;
                    switch (action.layer_bitop.op) {
                        case OP_BIT_AND: default_layer_and(bits | mask); break;
                        case OP_BIT_OR:  default_layer_or(bits | mask);  break;
                        case OP_BIT_XOR: default_layer_xor(bits | mask); break;
                        case OP_BIT_SET: default_layer_and(mask); default_layer_or(bits); break;
                    }
                }
            } else {
                /* Layer Bitwise Operation */
                if (event.pressed ? (action.layer_bitop.on & ON_PRESS) :
                                    (action.layer_bitop.on & ON_RELEASE)) {
                    uint8_t shift = action.layer_bitop.part*4;
                    uint32_t bits = ((uint32_t)action.layer_bitop.bits)<<shift;
                    uint32_t mask = (action.layer_bitop.xbit) ? ~(((uint32_t)0xf)<<shift) : 0;
                    switch (action.layer_bitop.op) {
                        case OP_BIT_AND: layer_and(bits | mask); break;
                        case OP_BIT_OR:  layer_or(bits | mask);  break;
                        case OP_BIT_XOR: layer_xor(bits | mask); break;
                        case OP_BIT_SET: layer_and(mask); layer_or(bits); break;
                    }
                }
            }
            break;
    #ifndef NO_ACTION_TAPPING
        case ACT_LAYER_TAP:
        case ACT_LAYER_TAP_EXT:
            switch (action.layer_tap.code) {
                case 0xe0 ... 0xef:
                    /* layer On/Off with modifiers(left only) */
                    if (event.pressed) {
                        layer_on(action.layer_tap.val);
                        register_mods(action.layer_tap.code & 0x0f);
                    } else {
                        layer_off(action.layer_tap.val);
                        unregister_mods(action.layer_tap.code & 0x0f);
                    }
                    break;
                case OP_TAP_TOGGLE:
                    /* tap toggle */
                    if (event.pressed) {
                        if (tap_count < TAPPING_TOGGLE) {
                            layer_invert(action.layer_tap.val);
                        }
                    } else {
                        if (tap_count <= TAPPING_TOGGLE) {
                            layer_invert(action.layer_tap.val);
                        }
                    }
                    break;
                case OP_ON_OFF:
                    event.pressed ? layer_on(action.layer_tap.val) :
                                    layer_off(action.layer_tap.val);
                    break;
                case OP_OFF_ON:
                    event.pressed ? layer_off(action.layer_tap.val) :
                                    layer_on(action.layer_tap.val);
                    break;
                case OP_SET_CLEAR:
                    event.pressed ? layer_move(action.layer_tap.val) :
                                    layer_clear();
                    break;
                default:
                    /* tap key */
                    if (event.pressed) {
                        if (tap_count > 0) {
                            dprint("KEYMAP_TAP_KEY: Tap: register_code\n");
                            register_code(action.layer_tap.code);
                        } else {
                            dprint("KEYMAP_TAP_KEY: No tap: On on press\n");
                            layer_on(action.layer_tap.val);
                        }
                    } else {
                        if (tap_count > 0) {
                            dprint("KEYMAP_TAP_KEY: Tap: unregister_code\n");
                            unregister_code(action.layer_tap.code);
                        } else {
                            dprint("KEYMAP_TAP_KEY: No tap: Off on release\n");
                            layer_off(action.layer_tap.val);
                        }
                    }
                    break;
            }
            break;
    #endif
#endif
        /* Extentions */
#ifndef NO_ACTION_MACRO
        case ACT_MACRO:
            action_macro_play(action_get_macro(record, action.func.id, action.func.opt));
            break;
#endif
#ifdef BACKLIGHT_ENABLE
        case ACT_BACKLIGHT:
            if (!event.pressed) {
                switch (action.backlight.opt) {
                    case BACKLIGHT_INCREASE:
                        backlight_increase();
                        break;
                    case BACKLIGHT_DECREASE:
                        backlight_decrease();
                        break;
                    case BACKLIGHT_TOGGLE:
                        backlight_toggle();
                        break;
                    case BACKLIGHT_STEP:
                        backlight_step();
                        break;
                    case BACKLIGHT_LEVEL:
                        backlight_level(action.backlight.level);
                        break;
                }
            }
            break;
#endif
        case ACT_COMMAND:
            break;
#ifndef NO_ACTION_FUNCTION
        case ACT_FUNCTION:
            action_function(record, action.func.id, action.func.opt);
            break;
#endif
        default:
            break;
    }
