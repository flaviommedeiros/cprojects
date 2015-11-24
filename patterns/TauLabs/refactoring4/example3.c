#if STM32_HAS_USART6
if ((sdp->usart == USART1) || (sdp->usart == USART6))
#else
  if (sdp->usart == USART1)
#endif
    u->BRR = STM32_PCLK2 / config->speed;
  else
    u->BRR = STM32_PCLK1 / config->speed;
