switch (stPortSpeed) {
    case B0: uiPortSpeed = 0; break;
    case B50: uiPortSpeed = 50; break;
    case B75: uiPortSpeed = 75; break;
    case B110: uiPortSpeed = 110; break;
    case B134: uiPortSpeed = 134; break;
    case B150: uiPortSpeed = 150; break;
    case B300: uiPortSpeed = 300; break;
    case B600: uiPortSpeed = 600; break;
    case B1200: uiPortSpeed = 1200; break;
    case B1800: uiPortSpeed = 1800; break;
    case B2400: uiPortSpeed = 2400; break;
    case B4800: uiPortSpeed = 4800; break;
    case B9600: uiPortSpeed = 9600; break;
    case B19200: uiPortSpeed = 19200; break;
    case B38400: uiPortSpeed = 38400; break;
#  ifdef B57600
    case B57600: uiPortSpeed = 57600; break;
#  endif
#  ifdef B115200
    case B115200: uiPortSpeed = 115200; break;
#  endif
#  ifdef B230400
    case B230400: uiPortSpeed = 230400; break;
#  endif
#  ifdef B460800
    case B460800: uiPortSpeed = 460800; break;
#  endif
#  ifdef B921600
    case B921600: uiPortSpeed = 921600; break;
#  endif
    default: return 0;
  }
