switch(type)
   {
      case SCREEN_EVENT_MTOUCH_TOUCH:
      case SCREEN_EVENT_MTOUCH_RELEASE:
      case SCREEN_EVENT_MTOUCH_MOVE:
         process_touch_event(screen_event, type);
         break;
      case SCREEN_EVENT_KEYBOARD:
         process_keyboard_event(screen_event, type);
         break;
#ifdef HAVE_BB10
      case SCREEN_EVENT_GAMEPAD:
      case SCREEN_EVENT_JOYSTICK:
         process_gamepad_event(screen_event, type);
         break;
      case SCREEN_EVENT_DEVICE:
         {
            // A device was attached or removed.
            screen_device_t device;
            int attached;
            int type;

            screen_get_event_property_pv(screen_event,
                  SCREEN_PROPERTY_DEVICE, (void**)&device);
            screen_get_event_property_iv(screen_event,
                  SCREEN_PROPERTY_ATTACHED, &attached);

            if (attached)
               screen_get_device_property_iv(device,
                     SCREEN_PROPERTY_TYPE, &type);

            int i;

            if (attached && (type == SCREEN_EVENT_GAMEPAD || type == SCREEN_EVENT_JOYSTICK || type == SCREEN_EVENT_KEYBOARD))
            {
               for (i = 0; i < MAX_PADS; ++i)
               {
                  if (!devices[i].handle)
                  {
                     devices[i].handle = device;
                     loadController(&devices[i]);
                     break;
                  }
               }
            }
            else
            {
               for (i = 0; i < MAX_PADS; ++i)
               {
                  if (device == devices[i].handle)
                  {
                     RARCH_LOG("Device %s: Disconnected.\n", devices[i].id);
                     initController(&devices[i]);
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
