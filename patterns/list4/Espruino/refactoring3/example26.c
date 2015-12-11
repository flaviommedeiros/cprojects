switch (inf->baudRate) {
        case 50      : baud = B50     ;break;
        case 75      : baud = B75     ;break;
        case 110     : baud = B110    ;break;
        case 134     : baud = B134    ;break;
        case 150     : baud = B150    ;break;
        case 200     : baud = B200    ;break;
        case 300     : baud = B300    ;break;
        case 600     : baud = B600    ;break;
        case 1200    : baud = B1200   ;break;
        case 1800    : baud = B1800   ;break;
        case 2400    : baud = B2400   ;break;
        case 4800    : baud = B4800   ;break;
        case 9600    : baud = B9600   ;break;
        case 19200   : baud = B19200  ;break;
        case 38400   : baud = B38400  ;break;
        case 57600   : baud = B57600  ;break;
        case 115200  : baud = B115200 ;break;
        case 230400  : baud = B230400 ;break;
#ifndef __MACOSX__
        case 460800  : baud = B460800 ;break;
        case 500000  : baud = B500000 ;break;
        case 576000  : baud = B576000 ;break;
        case 921600  : baud = B921600 ;break;
        case 1000000 : baud = B1000000;break;
        case 1152000 : baud = B1152000;break;
        case 1500000 : baud = B1500000;break;
        case 2000000 : baud = B2000000;break;
        case 2500000 : baud = B2500000;break;
        case 3000000 : baud = B3000000;break;
        case 3500000 : baud = B3500000;break;
        case 4000000 : baud = B4000000;break;
#endif
      }
