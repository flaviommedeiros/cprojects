switch(timerHardwarePtr->irq) {
#if defined(STM32F10X)
    case TIM1_CC_IRQn:
        timerNVICConfigure(TIM1_UP_IRQn);
        break;
#endif
#ifdef STM32F303xC
    case TIM1_CC_IRQn:
        timerNVICConfigure(TIM1_UP_TIM16_IRQn);
        break;
#endif
#if defined(STM32F10X_XL)
    case TIM8_CC_IRQn:
        timerNVICConfigure(TIM8_UP_IRQn);
        break;
#endif
    }
