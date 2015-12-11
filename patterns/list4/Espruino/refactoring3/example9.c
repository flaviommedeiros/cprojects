switch (spi_master_instance)
    {
        #ifdef SPI_MASTER_0_ENABLE
        case SPI_MASTER_0:
        {
            spi_config.SPI_Pin_SCK  = SPIM0_SCK_PIN;
            spi_config.SPI_Pin_MISO = SPIM0_MISO_PIN;
            spi_config.SPI_Pin_MOSI = SPIM0_MOSI_PIN;
            spi_config.SPI_Pin_SS   = SPIM0_SS_PIN;
        }
        break;
        #endif /* SPI_MASTER_0_ENABLE */

        #ifdef SPI_MASTER_1_ENABLE
        case SPI_MASTER_1:
        {
            spi_config.SPI_Pin_SCK  = SPIM1_SCK_PIN;
            spi_config.SPI_Pin_MISO = SPIM1_MISO_PIN;
            spi_config.SPI_Pin_MOSI = SPIM1_MOSI_PIN;
            spi_config.SPI_Pin_SS   = SPIM1_SS_PIN;
        }
        break;
        #endif /* SPI_MASTER_1_ENABLE */

        default:
            break;
    }
