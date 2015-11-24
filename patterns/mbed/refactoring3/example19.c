switch ((int)obj->spi.spi) {
#ifdef USART0
        case SPI_0:
            return cmuClock_USART0;
#endif
#ifdef USART1
        case SPI_1:
            return cmuClock_USART1;
#endif
#ifdef USART2
        case SPI_2:
            return cmuClock_USART2;
#endif
        default:
            error("Spi module not available.. Out of bound access.");
            return cmuClock_HFPER;
    }
