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
