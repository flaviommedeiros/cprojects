switch ((uint32_t)obj->serial.periph.uart) {
#ifdef UART0
        case UART_0:
            return cmuClock_UART0;
#endif
#ifdef UART1
        case UART_1:
            return cmuClock_UART1;
#endif
#ifdef USART0
        case USART_0:
            return cmuClock_USART0;
#endif
#ifdef USART1
        case USART_1:
            return cmuClock_USART1;
#endif
#ifdef USART2
        case USART_2:
            return cmuClock_USART2;
#endif
#ifdef LEUART0
        case LEUART_0:
            return cmuClock_LEUART0;
#endif
#ifdef LEUART1
        case LEUART_1:
            return cmuClock_LEUART1;
#endif
        default:
            return cmuClock_HFPER;
    }
