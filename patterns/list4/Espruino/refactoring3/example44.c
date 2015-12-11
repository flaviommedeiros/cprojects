switch (device) {
   case EV_SERIAL1 : return USART1;
   case EV_SERIAL2 : return USART2;
#ifdef USART3
   case EV_SERIAL3 : return USART3;
#endif
#ifdef UART4
   case EV_SERIAL4 : return UART4;
#endif
#ifdef UART5
   case EV_SERIAL5 : return UART5;
#endif
#ifdef USART6
   case EV_SERIAL6 : return USART6;
#endif
   default: return 0;
 }
