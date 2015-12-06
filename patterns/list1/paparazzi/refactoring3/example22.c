switch (cmd) {
    case DC_SHOOT:
      DC_PUSH(DC_SHUTTER_SERVO);
#ifndef DC_SHOOT_ON_BUTTON_RELEASE
      dc_send_shot_position();
#endif
      break;
#ifdef DC_ZOOM_IN_SERVO
    case DC_TALLER:
      DC_PUSH(DC_ZOOM_IN_SERVO);
      break;
#endif
#ifdef DC_ZOOM_OUT_SERVO
    case DC_WIDER:
      DC_PUSH(DC_ZOOM_OUT_SERVO);
      break;
#endif
#ifdef DC_POWER_SERVO
    case DC_ON:
      DC_PUSH(DC_POWER_SERVO);
      break;
#endif
    default:
      break;
  }
