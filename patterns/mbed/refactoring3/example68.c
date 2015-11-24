switch((uint32_t)(obj->serial.periph.uart)) {
#ifdef UART0
            case UART_0:
                channelConfig.select = DMAREQ_UART0_TXBL;
                break;
#endif
#ifdef UART1
            case UART_1:
                channelConfig.select = DMAREQ_UART1_TXBL;
                break;
#endif
#ifdef USART0
            case USART_0:
                channelConfig.select = DMAREQ_USART0_TXBL;
                break;
#endif
#ifdef USART1
            case USART_1:
                channelConfig.select = DMAREQ_USART1_TXBL;
                break;
#endif
#ifdef USART2
            case USART_2:
                channelConfig.select = DMAREQ_USART2_TXBL;
                break;
#endif
#ifdef LEUART0
            case LEUART_0:
                channelConfig.select = DMAREQ_LEUART0_TXBL;
                break;
#endif
#ifdef LEUART1
            case LEUART_1:
                channelConfig.select = DMAREQ_LEUART1_TXBL;
                break;
#endif
        }
