switch ((uint32_t)obj->serial.periph.uart) {
#ifdef UART0
        case UART_0:
            return UART0_TX_IRQn;
#endif
#ifdef UART1
        case UART_1:
            return UART1_TX_IRQn;
#endif
#ifdef USART0
        case USART_0:
            return USART0_TX_IRQn;
#endif
#ifdef USART1
        case USART_1:
            return USART1_TX_IRQn;
#endif
#ifdef USART2
        case USART_2:
            return USART2_TX_IRQn;
#endif
#ifdef LEUART0
        case LEUART_0:
            return LEUART0_IRQn;
#endif
#ifdef LEUART1
        case LEUART_1:
            return LEUART1_IRQn;
#endif
        default:
            MBED_ASSERT(0);
    }
