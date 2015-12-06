#if defined(STM32L100xBA) || defined (STM32L151xBA) || defined (STM32L152xBA) || defined(STM32L100xC) || defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC) || defined(STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE)
if((hrtc->Instance->CR & RTC_CR_BYPSHAD) == RESET)
#endif /* STM32L100xBA || STM32L151xBA || STM32L152xBA || STM32L100xC || STM32L151xC || STM32L152xC || STM32L162xC || STM32L151xCA || STM32L151xD || STM32L152xCA || STM32L152xD || STM32L162xCA || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE */
  {
    /* Clear RSF flag */
    hrtc->Instance->ISR &= (uint32_t)RTC_RSF_MASK;
    
  tickstart = HAL_GetTick();

    /* Wait the registers to be synchronised */
    while((hrtc->Instance->ISR & RTC_ISR_RSF) == (uint32_t)RESET)
    {
    if((HAL_GetTick() - tickstart ) >  RTC_TIMEOUT_VALUE)
      {       
        return HAL_TIMEOUT;
      } 
    }
  }
