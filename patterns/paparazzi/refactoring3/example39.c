switch (sdl_event.jbutton.button) {
#ifndef NPS_JS_AXIS_MODE
          case NPS_JS_BUTTON_MODE_MANUAL:
            nps_joystick.mode = MODE_SWITCH_MANUAL;
            break;

          case NPS_JS_BUTTON_MODE_AUTO1:
            nps_joystick.mode = MODE_SWITCH_AUTO1;
            break;

          case NPS_JS_BUTTON_MODE_AUTO2:
            nps_joystick.mode = MODE_SWITCH_AUTO2;
            break;
#endif
          default:
            //ignore
            break;
        }
