switch (timer_peripheral) {
      // Timers on high speed APB2
    case TIM1:
    case TIM8:
#ifdef TIM9
    case TIM9:
#endif
#ifdef TIM10
    case TIM10:
#endif
#ifdef TIM11
    case TIM11:
#endif
      if (!rcc_get_ppre2())
      {
        /* without APB2 prescaler, runs at APB2 freq */
        return rcc_apb2_frequency;
      } else {
        /* with any ABP2 prescaler, runs at 2 * APB2 freq */
        return rcc_apb2_frequency * 2;
      }

      // timers on low speed APB1
    case TIM2:
    case TIM3:
    case TIM4:
    case TIM5:
    case TIM6:
    case TIM7:
#ifdef TIM12
    case TIM12:
#endif
#ifdef TIM13
    case TIM13:
#endif
#ifdef TIM14
    case TIM14:
#endif
      if (!rcc_get_ppre1())
      {
        /* without APB1 prescaler, runs at APB1 freq */
        return rcc_apb1_frequency;
      } else {
        /* with any ABP1 prescaler, runs at 2 * APB1 freq */
        return rcc_apb1_frequency * 2;
      }
    default:
      // other timers currently not supported
      break;
  }
