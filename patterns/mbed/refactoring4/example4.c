#if  defined(STM32F101xG) || defined(STM32F103xG)
if(__HAL_FLASH_GET_FLAG(FLASH_FLAG_PGERR) || __HAL_FLASH_GET_FLAG(FLASH_FLAG_PGERR_BANK2))
#else
  if(__HAL_FLASH_GET_FLAG(FLASH_FLAG_PGERR))
#endif /* STM32F101xG || STM32F103xG */
  {
     pFlash.ErrorCode |= HAL_FLASH_ERROR_PROG;
  }
