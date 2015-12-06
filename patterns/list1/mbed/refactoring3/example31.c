switch ((uint32_t)obj->serial.periph.uart) {
#ifdef UART0
        case UART_0:
            return 0;
#endif
#ifdef UART1
        case UART_1:
            return 1;
#endif
#ifdef USART0
        case USART_0:
            return 2;
#endif
#ifdef USART1
        case USART_1:
            return 3;
#endif
#ifdef USART2
        case USART_2:
            return 4;
#endif
#ifdef LEUART0
        case LEUART_0:
            return 5;
#endif
#ifdef LEUART1
        case LEUART_1:
            return 6;
#endif
    }
