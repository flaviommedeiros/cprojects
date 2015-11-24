switch ((int)obj->spi.spi) {
#ifdef USART0
        case SPI_0:
            rxChnlCfg.select = DMAREQ_USART0_RXDATAV;
            txChnlCfg.select = DMAREQ_USART0_TXEMPTY;
            break;
#endif
#ifdef USART1
        case SPI_1:
            rxChnlCfg.select = DMAREQ_USART1_RXDATAV;
            txChnlCfg.select = DMAREQ_USART1_TXEMPTY;
            break;
#endif
#ifdef USART2
        case SPI_2:
            rxChnlCfg.select = DMAREQ_USART2_RXDATAV;
            txChnlCfg.select = DMAREQ_USART2_TXEMPTY;
            break;
#endif
        default:
            error("Spi module not available.. Out of bound access.");
            break;
    }
