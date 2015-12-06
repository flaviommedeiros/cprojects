switch(baudrate) {
  case -2:
    break;			/* Use default. */
  case 9600:
    slip_config_b_rate = B9600;
    break;
  case 19200:
    slip_config_b_rate = B19200;
    break;
  case 38400:
    slip_config_b_rate = B38400;
    break;
  case 57600:
    slip_config_b_rate = B57600;
    break;
  case 115200:
    slip_config_b_rate = B115200;
    break;
#ifdef linux
  case 921600:
    slip_config_b_rate = B921600;
    break;
#endif
  default:
    err(1, "unknown baudrate %d", baudrate);
    break;
  }
