switch (self->speed)
    {
    case 2400:
    case 4800:
    case 9600:
    case 19200:
    case 38400:
    case 57600:
    case 115200:
#ifdef USE_MIR
    case 1152000:
#endif
    case 4000000:
      break;
    default:

      printk (KERN_ERR DRIVER_NAME ": switch to unsupported baudrate %d\n",
              self->speed);
      return;
    }
