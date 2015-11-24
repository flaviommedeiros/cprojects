switch (port) {
    case GPIOA:
      rcc_periph_clock_enable(RCC_GPIOA);
      break;
    case GPIOB:
      rcc_periph_clock_enable(RCC_GPIOB);
      break;
    case GPIOC:
      rcc_periph_clock_enable(RCC_GPIOC);
      break;
    case GPIOD:
      rcc_periph_clock_enable(RCC_GPIOD);
      break;
#ifdef GPIOE
    case GPIOE:
      rcc_periph_clock_enable(RCC_GPIOE);
      break;
#endif
#ifdef GPIOF
    case GPIOF:
      rcc_periph_clock_enable(RCC_GPIOF);
      break;
#endif
#ifdef GPIOG
    case GPIOG:
      rcc_periph_clock_enable(RCC_GPIOG);
      break;
#endif
#ifdef GPIOH
    case GPIOH:
      rcc_periph_clock_enable(RCC_GPIOH);
      break;
#endif
#ifdef GPIOI
    case GPIOI:
      rcc_periph_clock_enable(RCC_GPIOI);
      break;
#endif
    default:
      break;
  }
