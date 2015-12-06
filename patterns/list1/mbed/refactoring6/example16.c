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
