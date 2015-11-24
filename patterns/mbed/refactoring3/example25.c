switch ((uint32_t)obj->spi.spi) {
#ifdef USART0
        case USART_0:
            IRQvector = USART0_RX_IRQn;
            break;
#endif
#ifdef USART1
        case USART_1:
            IRQvector = USART1_RX_IRQn;
            break;
#endif
#ifdef USART2
        case USART_2:
            IRQvector = USART2_RX_IRQn;
            break;
#endif
        default:
            error("Undefined SPI peripheral");
            return;
    }
