switch (device) {
  case EV_LOOPBACKA: return "LoopbackA";
  case EV_LOOPBACKB: return "LoopbackB";
  case EV_LIMBO: return "Limbo";
#ifdef USB
  case EV_USBSERIAL: return "USB";
#endif
#ifdef BLUETOOTH
  case EV_BLUETOOTH: return "Bluetooth";
#endif
  case EV_SERIAL1: return "Serial1";
  case EV_SERIAL2: return "Serial2";
  case EV_SERIAL3: return "Serial3";
#if USART_COUNT>=4
  case EV_SERIAL4: return "Serial4";
#endif
#if USART_COUNT>=5
  case EV_SERIAL5: return "Serial5";
#endif
#if USART_COUNT>=6
  case EV_SERIAL6: return "Serial6";
#endif
#if SPI_COUNT>=1
  case EV_SPI1: return "SPI1";
#endif
#if SPI_COUNT>=2
  case EV_SPI2: return "SPI2";
#endif
#if SPI_COUNT>=3
  case EV_SPI3: return "SPI3";
#endif
#if I2C_COUNT>=1
  case EV_I2C1: return "I2C1";
#endif
#if I2C_COUNT>=2
  case EV_I2C2: return "I2C2";
#endif
#if I2C_COUNT>=3
  case EV_I2C3: return "I2C3";
#endif
  default: return "";
  }
