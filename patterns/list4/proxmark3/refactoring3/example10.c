switch (uiPortSpeed) {
    case 0: stPortSpeed = B0; break;
    case 50: stPortSpeed = B50; break;
    case 75: stPortSpeed = B75; break;
    case 110: stPortSpeed = B110; break;
    case 134: stPortSpeed = B134; break;
    case 150: stPortSpeed = B150; break;
    case 300: stPortSpeed = B300; break;
    case 600: stPortSpeed = B600; break;
    case 1200: stPortSpeed = B1200; break;
    case 1800: stPortSpeed = B1800; break;
    case 2400: stPortSpeed = B2400; break;
    case 4800: stPortSpeed = B4800; break;
    case 9600: stPortSpeed = B9600; break;
    case 19200: stPortSpeed = B19200; break;
    case 38400: stPortSpeed = B38400; break;
#  ifdef B57600
    case 57600: stPortSpeed = B57600; break;
#  endif
#  ifdef B115200
    case 115200: stPortSpeed = B115200; break;
#  endif
#  ifdef B230400
    case 230400: stPortSpeed = B230400; break;
#  endif
#  ifdef B460800
    case 460800: stPortSpeed = B460800; break;
#  endif
#  ifdef B921600
    case 921600: stPortSpeed = B921600; break;
#  endif
    default: return false;
  }
