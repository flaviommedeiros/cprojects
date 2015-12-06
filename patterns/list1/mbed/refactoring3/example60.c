switch ((uint32_t)obj->serial.periph.uart) {
#ifdef UART0
        case UART_0:
            NVIC_SetVector(UART0_RX_IRQn, (uint32_t) &uart0_rx_irq);
            NVIC_SetVector(UART0_TX_IRQn, (uint32_t) &uart0_tx_irq);
            NVIC_SetPriority(UART0_TX_IRQn, 1);
            break;
#endif
#ifdef UART1
        case UART_1:
            NVIC_SetVector(UART1_RX_IRQn, (uint32_t) &uart1_rx_irq);
            NVIC_SetVector(UART1_TX_IRQn, (uint32_t) &uart1_tx_irq);
            NVIC_SetPriority(UART1_TX_IRQn, 1);
            break;
#endif
#ifdef USART0
        case USART_0:
            NVIC_SetVector(USART0_RX_IRQn, (uint32_t) &usart0_rx_irq);
            NVIC_SetVector(USART0_TX_IRQn, (uint32_t) &usart0_tx_irq);
            NVIC_SetPriority(USART0_TX_IRQn, 1);
            break;
#endif
#ifdef USART1
        case USART_1:
            NVIC_SetVector(USART1_RX_IRQn, (uint32_t) &usart1_rx_irq);
            NVIC_SetVector(USART1_TX_IRQn, (uint32_t) &usart1_tx_irq);
            NVIC_SetPriority(USART1_TX_IRQn, 1);
            break;
#endif
#ifdef USART2
        case USART_2:
            NVIC_SetVector(USART2_RX_IRQn, (uint32_t) &usart2_rx_irq);
            NVIC_SetVector(USART2_TX_IRQn, (uint32_t) &usart2_tx_irq);
            NVIC_SetPriority(USART2_TX_IRQn, 1);
            break;
#endif
#ifdef LEUART0
        case LEUART_0:
            NVIC_SetVector(LEUART0_IRQn, (uint32_t) &leuart0_irq);
            break;
#endif
#ifdef LEUART1
        case LEUART_1:
            NVIC_SetVector(LEUART1_IRQn, (uint32_t) &leuart1_irq);
            break;
#endif
    }
