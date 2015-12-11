switch (spi_master_hw_instance)
    {
    #ifdef SPI_MASTER_0_ENABLE
        case SPI_MASTER_0:
            spi_master_init_hw_instance(NRF_SPI0, SPI0_TWI0_IRQn, p_spi_instance, p_spi_master_config->SPI_DisableAllIRQ);
            break;
    #endif /* SPI_MASTER_0_ENABLE */

    #ifdef SPI_MASTER_1_ENABLE
        case SPI_MASTER_1:
            spi_master_init_hw_instance(NRF_SPI1, SPI1_TWI1_IRQn, p_spi_instance, p_spi_master_config->SPI_DisableAllIRQ);
            break;
    #endif /* SPI_MASTER_1_ENABLE */

        default:
            break;
    }
