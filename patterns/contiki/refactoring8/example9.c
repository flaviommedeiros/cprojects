char
SPI_Read(enum CSI_Bus bus,
         char slaveDeviceId,
         unsigned char *data,
         char bytesNumber)
{
#if BITBANG_SPI
  unsigned char n = 0;
  for(n = 0; n < bytesNumber; n++) {
    data[n] = spi_byte_exchange(data[n]);
  }
#else
  char byte = 0;
  unsigned short originalSCR = 0;
  unsigned short originalSO1 = 0;

  volatile uint8_t *sio;
  volatile uint16_t *ssr;
  char dummy;

  switch(bus) {
  default:
  case CSI00: sio = &SIO00;
    ssr = &SSR00;
    break;
  case CSI01: sio = &SIO01;
    ssr = &SSR01;
    break;
  case CSI10: sio = &SIO10;
    ssr = &SSR02;
    break;
  case CSI11: sio = &SIO11;
    ssr = &SSR03;
    break;
  case CSI20: sio = &SIO20;
    ssr = &SSR10;
    break;
  case CSI21: sio = &SIO21;
    ssr = &SSR11;
    break;
  case CSI30: sio = &SIO30;
    ssr = &SSR12;
    break;
  case CSI31: sio = &SIO31;
    ssr = &SSR13;
    break;
  }

  /* Flush the receive buffer: */
  while(*ssr & 0x0020) dummy = *sio;
  (void)dummy;

  for(byte = 0; byte < bytesNumber; byte++) {
    *sio = data[byte];
    NOP;
    while(*ssr & 0x0040) ;
    data[byte] = *sio;
  }
#endif

  return bytesNumber;
}
