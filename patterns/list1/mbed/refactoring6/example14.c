if( (__HAL_FLASH_GET_FLAG(FLASH_FLAG_WRPERR)     != RESET) || 
        (__HAL_FLASH_GET_FLAG(FLASH_FLAG_PGAERR)     != RESET) || 
        (__HAL_FLASH_GET_FLAG(FLASH_FLAG_SIZERR)     != RESET) || 
#if defined (STM32L151xBA) || defined (STM32L152xBA) || \
    defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC)
        (__HAL_FLASH_GET_FLAG(FLASH_FLAG_RDERR)      != RESET) || 
#endif /* STM32L151xBA || STM32L152xBA || STM32L151xC || STM32L152xC || STM32L162xC */
#if defined(STM32L100xC) || defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC) || \
    defined(STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || \
    defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE)
        (__HAL_FLASH_GET_FLAG(FLASH_FLAG_OPTVERRUSR) != RESET) || 
#endif /* STM32L100xC || STM32L151xC || STM32L152xC || STM32L162xC || STM32L151xCA || STM32L151xD || STM32L152xCA || STM32L152xD || STM32L162xCA || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE */
        (__HAL_FLASH_GET_FLAG(FLASH_FLAG_OPTVERR)    != RESET) )
    {
      return HAL_ERROR;
    }
