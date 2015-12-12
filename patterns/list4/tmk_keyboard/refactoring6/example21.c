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
