switch(type)
   {
      case SCREEN_EVENT_MTOUCH_TOUCH:
      case SCREEN_EVENT_MTOUCH_RELEASE:
      case SCREEN_EVENT_MTOUCH_MOVE:
         qnx_process_touch_event(qnx, screen_event, type);
         break;
      case SCREEN_EVENT_KEYBOARD:
         qnx_process_keyboard_event(qnx, screen_event, type);
         break;
#ifdef HAVE_BB10
      case SCREEN_EVENT_GAMEPAD:
      case SCREEN_EVENT_JOYSTICK:
         qnx_process_gamepad_event(qnx, screen_event, type);
         break;
      case SCREEN_EVENT_DEVICE:
         {
            /* A device was attached or removed. */
            screen_device_t device;
            int attached, type, i;

            screen_get_event_property_pv(screen_event,
                  SCREEN_PROPERTY_DEVICE, (void**)&device);
            screen_get_event_property_iv(screen_event,
                  SCREEN_PROPERTY_ATTACHED, &attached);

            if (attached)
               screen_get_device_property_iv(device,
                     SCREEN_PROPERTY_TYPE, &type);

            if (attached && 
                  (
                   type == SCREEN_EVENT_GAMEPAD ||
                   type == SCREEN_EVENT_JOYSTICK ||
                   type == SCREEN_EVENT_KEYBOARD)
               )
            {
               for (i = 0; i < MAX_PADS; ++i)
               {
                  if (!qnx->devices[i].handle)
                  {
                     qnx->devices[i].handle = device;
                     qnx_handle_device(qnx, &qnx->devices[i]);
                     break;
                  }
               }
            }
            else
            {
               for (i = 0; i < MAX_PADS; ++i)
               {
                  if (device == qnx->devices[i].handle)
                  {
                     RARCH_LOG("Device %s: Disconnected.\n",
                           qnx->devices[i].id);
                     qnx_init_controller(qnx, &qnx->devices[i]);
                     break;
                  }
               }
            }
         }
         break;
#endif
      default:
         break;
   }
