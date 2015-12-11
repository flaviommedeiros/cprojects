if ((TIMx == TIM1)
#ifdef TIM8
      || (TIMx == TIM8)
#endif
      )
  {
    /* Set the Repetition Counter value */
    TIMx->RCR = TIM_TimeBaseInitStruct->TIM_RepetitionCounter;
  }
