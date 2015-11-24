const escHardware_t escHardware[ESC_COUNT] = {
// Figure out esc clocks and pins, extrapolated from timer.c
// Periphs could be pulled progmatically... but I'll leave that for another exercise
#if defined(STM32F3DISCOVERY) && !(defined(CHEBUZZF3))
  { GPIOD, 12 },
  { GPIOD, 13 },
  { GPIOD, 14 },
  { GPIOD, 15 },
  { GPIOA, 1 },
  { GPIOA, 2 }
#elif defined(CJMCU) || defined(EUSTM32F103RC) || defined(NAZE) || defined(OLIMEXINO) || defined(PORT103R)
  { GPIOA, 8 },
  { GPIOA, 11 },
  { GPIOB, 6 },
  { GPIOB, 7 },
  { GPIOB, 8 },
  { GPIOB, 9 }
#elif CC3D
  { GPIOB, 9 },
  { GPIOB, 8 },
  { GPIOB, 7 },
  { GPIOA, 8 },
  { GPIOB, 4 },
  { GPIOA, 2 }
#elif SPRACINGF3
  { GPIOA, 6 },
  { GPIOA, 7 },
  { GPIOA, 11 },
  { GPIOA, 12 },
  { GPIOB, 8 },
  { GPIOB, 9 },
  { GPIOA, 2 },
  { GPIOA, 3 }
#elif MOTOLAB
  { GPIOA, 4 },
  { GPIOA, 6 },
  { GPIOB, 0 },
  { GPIOB, 1 },
  { GPIOA, 1 },
  { GPIOA, 2 },
  { GPIOA, 3 },
  { GPIOA, 8 }
#elif SPARKY
  { GPIOB, 15 },
  { GPIOB, 14 },
  { GPIOA, 8 },
  { GPIOB, 0 },
  { GPIOA, 6 },
  { GPIOA, 2 }
#endif
};
