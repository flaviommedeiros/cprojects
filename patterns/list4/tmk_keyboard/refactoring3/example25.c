switch (wIndex) {
            case KEYBOARD_INTERFACE:
                Address = &ConfigurationDescriptor.Keyboard_HID;
                Size    = sizeof(USB_HID_Descriptor_HID_t);
                break;
#ifdef MOUSE_ENABLE
            case MOUSE_INTERFACE:
                Address = &ConfigurationDescriptor.Mouse_HID;
                Size    = sizeof(USB_HID_Descriptor_HID_t);
                break;
#endif
#ifdef EXTRAKEY_ENABLE
            case EXTRAKEY_INTERFACE:
                Address = &ConfigurationDescriptor.Extrakey_HID;
                Size    = sizeof(USB_HID_Descriptor_HID_t);
                break;
#endif
#ifdef CONSOLE_ENABLE
            case CONSOLE_INTERFACE:
                Address = &ConfigurationDescriptor.Console_HID;
                Size    = sizeof(USB_HID_Descriptor_HID_t);
                break;
#endif
#ifdef NKRO_ENABLE
            case NKRO_INTERFACE:
                Address = &ConfigurationDescriptor.NKRO_HID;
                Size    = sizeof(USB_HID_Descriptor_HID_t);
                break;
#endif
            }
