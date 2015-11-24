switch ((int)obj->spi.spi) {
#ifdef USART0
        case SPI_0:
            index = 0;
            break;
#endif
#ifdef USART1
        case SPI_1:
            index = 1;
            break;
#endif
#ifdef USART2
        case SPI_2:
            index = 2;
            break;
#endif
        default:
            error("Spi module not available.. Out of bound access.");
            break;
    }
