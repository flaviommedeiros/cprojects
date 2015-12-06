if((((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_RTC) == RCC_PERIPHCLK_RTC)
#if defined (STM32L053xx) || defined(STM32L063xx) || defined(STM32L073xx) || defined(STM32L083xx)
    || (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_LCD) == RCC_PERIPHCLK_LCD)
#endif /* defined (STM32L053xx) || defined(STM32L063xx) || defined(STM32L073xx) || defined(STM32L083xx) */
  )
  {
        /* Enable Power Clock*/
    __HAL_RCC_PWR_CLK_ENABLE();
    
    /* Enable write access to Backup domain */
    PWR->CR |= PWR_CR_DBP;
    
    /* Wait for Backup domain Write protection disable */
    tickstart = HAL_GetTick();
    
    while((PWR->CR & PWR_CR_DBP) == RESET)
    {
      if((HAL_GetTick() - tickstart ) > RCC_DBP_TIMEOUT_VALUE)
      {
        return HAL_TIMEOUT;
      }      
    }
    
    /* Reset the Backup domain only if the RTC Clock source selection is modified */ 
    if(((RCC->CSR & RCC_CSR_RTCSEL) != (PeriphClkInit->RTCClockSelection & RCC_CSR_RTCSEL))
#if defined (STM32L053xx) || defined(STM32L063xx) || defined(STM32L073xx) || defined(STM32L083xx)
    || (tmpreg != (PeriphClkInit->LCDClockSelection & RCC_CSR_RTCSEL))
#endif /* defined (STM32L053xx) || defined(STM32L063xx) || defined(STM32L073xx) || defined(STM32L083xx) */
    )
    {
      /* Store the content of CSR register before the reset of Backup Domain */
      tmpreg = (RCC->CSR & ~(RCC_CSR_RTCSEL));
      /* RTC Clock selection can be changed only if the Backup Domain is reset */
      __HAL_RCC_BACKUPRESET_FORCE();
      __HAL_RCC_BACKUPRESET_RELEASE();
      /* Restore the Content of CSR register */
      RCC->CSR = tmpreg;
    }
    
    /* If LSE is selected as RTC clock source, wait for LSE reactivation */
    if((PeriphClkInit->RTCClockSelection == RCC_RTCCLKSOURCE_LSE)
#if defined (STM32L053xx) || defined(STM32L063xx) || defined(STM32L073xx) || defined(STM32L083xx)
    || (PeriphClkInit->LCDClockSelection == RCC_RTCCLKSOURCE_LSE)
#endif /* defined (STM32L053xx) || defined(STM32L063xx) || defined(STM32L073xx) || defined(STM32L083xx) */
    )
    {
      /* Get timeout */   
      tickstart = HAL_GetTick();
      
      /* Wait till LSE is ready */  
      while(__HAL_RCC_GET_FLAG(RCC_FLAG_LSERDY) == RESET)
      {
        if((HAL_GetTick() - tickstart ) > RCC_LSE_TIMEOUT_VALUE)
        {
          return HAL_TIMEOUT;
        }      
      }  
    }
    __HAL_RCC_RTC_CONFIG(PeriphClkInit->RTCClockSelection);
  }
