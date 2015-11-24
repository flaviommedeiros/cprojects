switch (device)
   {
      case RETRO_DEVICE_JOYPAD:
         return input_joypad_pressed(ps3->joypad, port, binds[port], id);
      case RETRO_DEVICE_ANALOG:
         return input_joypad_analog(ps3->joypad, port, idx, id, binds[port]);
#if 0
      case RETRO_DEVICE_SENSOR_ACCELEROMETER:
         switch (id)
         {
            /* Fixed range of 0x000 - 0x3ff */
            case RETRO_DEVICE_ID_SENSOR_ACCELEROMETER_X:
               retval = ps3->accelerometer_state[port].x;
               break;
            case RETRO_DEVICE_ID_SENSOR_ACCELEROMETER_Y:
               retval = ps3->accelerometer_state[port].y;
               break;
            case RETRO_DEVICE_ID_SENSOR_ACCELEROMETER_Z:
               retval = ps3->accelerometer_state[port].z;
               break;
            default:
               retval = 0;
         }
         break;
#endif
#ifdef HAVE_MOUSE
      case RETRO_DEVICE_MOUSE:
         return ps3_mouse_device_state(data, port, id);
#endif
   }
