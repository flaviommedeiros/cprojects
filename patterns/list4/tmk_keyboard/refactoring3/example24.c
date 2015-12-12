switch (USB_ControlRequest.wIndex) {
                case KEYBOARD_INTERFACE:
#ifdef NKRO_ENABLE
                case NKRO_INTERFACE:
#endif
                    Endpoint_ClearSETUP();

                    while (!(Endpoint_IsOUTReceived())) {
                        if (USB_DeviceState == DEVICE_STATE_Unattached)
                          return;
                    }
                    keyboard_led_stats = Endpoint_Read_8();

                    Endpoint_ClearOUT();
                    Endpoint_ClearStatusStage();
                    break;
                }
