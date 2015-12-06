if ((((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_RTC) == RCC_PERIPHCLK_RTC) 
#if defined (STM32L100xB) || defined (STM32L100xBA) || defined (STM32L100xC) ||\
    defined(STM32L152xB) || defined(STM32L152xBA) || defined(STM32L152xC) || \
    defined(STM32L162xC) || defined(STM32L152xCA) || defined(STM32L152xD) || \
    defined(STM32L162xCA) || defined(STM32L162xD) || defined(STM32L152xE) || \
    defined(STM32L162xE)
    || (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_LCD) == RCC_PERIPHCLK_LCD)
#endif /* STM32L100xB || STM32L152xBA || ... || STM32L152xE || STM32L162xE */
    )
    {
    /* Enable Power Controller clock */
    __PWR_CLK_ENABLE();
    
    /* Enable write access to Backup domain */
    SET_BIT(PWR->CR, PWR_CR_DBP);

    /* Wait for Backup domain Write protection disable */
    tickstart = HAL_GetTick();
    
    while((PWR->CR & PWR_CR_DBP) == RESET)
    {
      if((HAL_GetTick() - tickstart ) > DBP_TIMEOUT_VALUE)
      {
        return HAL_TIMEOUT;
      }      
    }
    
    tmpreg = (RCC->CSR & RCC_CSR_RTCSEL);
    /* Reset the Backup domain only if the RTC Clock source selection is modified */ 
    if((tmpreg != (PeriphClkInit->RTCClockSelection & RCC_CSR_RTCSEL))
#if defined (STM32L100xB) || defined (STM32L100xBA) || defined (STM32L100xC) ||\
    defined(STM32L152xB) || defined(STM32L152xBA) || defined(STM32L152xC) || \
    defined(STM32L162xC) || defined(STM32L152xCA) || defined(STM32L152xD) || \
    defined(STM32L162xCA) || defined(STM32L162xD) || defined(STM32L152xE) || \
    defined(STM32L162xE)
    || (tmpreg != (PeriphClkInit->LCDClockSelection & RCC_CSR_RTCSEL))
#endif /* STM32L100xB || STM32L152xBA || ... || STM32L152xE || STM32L162xE */
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
    if ((PeriphClkInit->RTCClockSelection == RCC_RTCCLKSOURCE_LSE)
#if defined (STM32L100xB) || defined (STM32L100xBA) || defined (STM32L100xC) ||\
    defined(STM32L152xB) || defined(STM32L152xBA) || defined(STM32L152xC) || \
    defined(STM32L162xC) || defined(STM32L152xCA) || defined(STM32L152xD) || \
    defined(STM32L162xCA) || defined(STM32L162xD) || defined(STM32L152xE) || \
    defined(STM32L162xE)
    || (PeriphClkInit->LCDClockSelection == RCC_RTCCLKSOURCE_LSE)
#endif /* STM32L100xB || STM32L152xBA || ... || STM32L152xE || STM32L162xE */
      )
    {
      /* Get timeout */   
      tickstart = HAL_GetTick();
      
      /* Wait till LSE is ready */  
      while(__HAL_RCC_GET_FLAG(RCC_FLAG_LSERDY) == RESET)
      {
        if((HAL_GetTick() - tickstart ) > LSE_TIMEOUT_VALUE)
        {
          return HAL_TIMEOUT;
        }      
      }  
    }

    __HAL_RCC_RTC_CONFIG(PeriphClkInit->RTCClockSelection);
  }
