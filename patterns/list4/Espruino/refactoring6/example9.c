if ((TIMx == TIM1)
#ifdef TIM8
      || (TIMx == TIM8)
#endif
      )
  {
    assert_param(IS_TIM_OCIDLE_STATE(TIM_OCInitStruct->TIM_OCIdleState));
    /* Reset the Output Compare IDLE State */
    tmpcr2 &=(uint16_t) ~TIM_CR2_OIS4;
    /* Set the Output Idle state */
    tmpcr2 |= (uint16_t)(TIM_OCInitStruct->TIM_OCIdleState << 6);
  }
