switch (cmd) {
    case DC_SHOOT:
      DC_PUSH(DC_SHUTTER_GPIO);
#ifndef DC_SHOOT_ON_BUTTON_RELEASE
      dc_send_shot_position();
#endif
      break;
#ifdef DC_ZOOM_IN_GPIO
    case DC_TALLER:
      DC_PUSH(DC_ZOOM_IN_GPIO);
      break;
#endif
#ifdef DC_ZOOM_OUT_GPIO
    case DC_WIDER:
      DC_PUSH(DC_ZOOM_OUT_GPIO);
      break;
#endif
#ifdef DC_POWER_GPIO
    case DC_ON:
      DC_PUSH(DC_POWER_GPIO);
      break;
#endif
#ifdef DC_POWER_OFF_GPIO
    case DC_OFF:
      DC_PUSH(DC_POWER_OFF_GPIO);
      dc_timer = DC_POWER_OFF_DELAY * GPIO_CAM_CTRL_PERIODIC_FREQ;
      break;
#endif
    default:
      break;
  }
