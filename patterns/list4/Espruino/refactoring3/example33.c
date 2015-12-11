switch (device&JSH_MASK_TYPE) {
    case JSH_TIMER1:
      return TIM1;
    case JSH_TIMER2:
      return TIM2;
    case JSH_TIMER3:
      return TIM3;
    case JSH_TIMER4:
      return TIM4;
#ifndef STM32F3
    case JSH_TIMER5:
      return TIM5;
#endif
#ifdef TIM6
    case JSH_TIMER6: // Not used for outputs
      return TIM6;
#endif
#ifdef TIM7
    case JSH_TIMER7:
      return TIM7;
#endif
#ifdef TIM8
    case JSH_TIMER8:
      return TIM8;
#endif
#ifdef TIM9
    case JSH_TIMER9:
      return TIM9;
#endif
#ifdef TIM10
    case JSH_TIMER10:
      return TIM10;
#endif
#ifdef TIM11
    case JSH_TIMER11:
      return TIM11;
#endif
#ifdef TIM12
    case JSH_TIMER12:
      return TIM12;
#endif
#ifdef TIM13
    case JSH_TIMER13:
      return TIM13;
#endif
#ifdef TIM14
    case JSH_TIMER14:
      return TIM14;
#endif
#ifdef TIM15
    case JSH_TIMER15:
      return TIM15;
#endif
#ifdef TIM16
    case JSH_TIMER16:
      return TIM16;
#endif
#ifdef TIM17
    case JSH_TIMER17:
      return TIM17;
#endif

  }
