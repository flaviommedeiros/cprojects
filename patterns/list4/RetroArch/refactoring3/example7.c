switch (device)
   {
      case RETRO_DEVICE_JOYPAD:
         if(port_device[port])
         {
            if (port_device[port]->device == DEVICE_KEYBOARD || port_device[port]->device == DEVICE_KEYPAD)
               return ((port_device[port]->buttons & (1 << id)) && (port < pads_connected) );
            else{
               return ((port_device[port]->buttons & retro_keybinds[port][id].joykey) && (port < pads_connected));
            }
         }
         break;
#ifdef HAVE_BB10
      case RETRO_DEVICE_ANALOG:
         //Need to return [-0x8000, 0x7fff]
         //Gamepad API gives us [-128, 127] with (0,0) center
         //Untested
         if(port_device[port])
         {
            switch ((index << 1) | id)
            {
               case (RETRO_DEVICE_INDEX_ANALOG_LEFT << 1) | RETRO_DEVICE_ID_ANALOG_X:
                  return port_device[port]->analog0[0] * 256;
               case (RETRO_DEVICE_INDEX_ANALOG_LEFT << 1) | RETRO_DEVICE_ID_ANALOG_Y:
                  return port_device[port]->analog0[1] * 256;
               case (RETRO_DEVICE_INDEX_ANALOG_RIGHT << 1) | RETRO_DEVICE_ID_ANALOG_X:
                  return port_device[port]->analog1[0] * 256;
               case (RETRO_DEVICE_INDEX_ANALOG_RIGHT << 1) | RETRO_DEVICE_ID_ANALOG_Y:
                  return port_device[port]->analog1[1] * 256;
               default:
                  break;
            }
         }
         break;
#endif
      case RARCH_DEVICE_POINTER_SCREEN:
      case RETRO_DEVICE_POINTER:
         {
            const bool want_full = device == RARCH_DEVICE_POINTER_SCREEN;

            switch (id)
            {
               case RETRO_DEVICE_ID_POINTER_X: return want_full ? touch[touch_map[index]].full_x : touch[touch_map[index]].x;
               case RETRO_DEVICE_ID_POINTER_Y: return want_full ? touch[touch_map[index]].full_y : touch[touch_map[index]].y;
               case RETRO_DEVICE_ID_POINTER_PRESSED: return (touch_map[index] != -1);
            }

            break;
         }
      default:
         break;
   }
