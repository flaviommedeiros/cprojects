#if STM32_HAS_USART6
if ((uartp->usart == USART1) || (uartp->usart == USART6))
#else
  if (uartp->usart == USART1)
#endif
    u->BRR = STM32_PCLK2 / uartp->config->speed;
  else
    u->BRR = STM32_PCLK1 / uartp->config->speed;
