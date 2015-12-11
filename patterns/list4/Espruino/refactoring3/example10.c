switch (m_spi_master_ex_state)
    {
        #ifdef SPI_MASTER_0_ENABLE
        case TEST_STATE_SPI0_LSB:
            spi_master_init(SPI_MASTER_0, spi_master_0_event_handler, true);

            spi_send_recv(SPI_MASTER_0, m_tx_data_spi, m_rx_data_spi, TX_RX_MSG_LENGTH);
            m_spi_master_ex_state = TEST_STATE_SPI0_MSB;

            break;

        case TEST_STATE_SPI0_MSB:
            spi_master_init(SPI_MASTER_0, spi_master_0_event_handler, false);

            spi_send_recv(SPI_MASTER_0, m_tx_data_spi, m_rx_data_spi, TX_RX_MSG_LENGTH);

            #ifdef SPI_MASTER_1_ENABLE
            m_spi_master_ex_state = TEST_STATE_SPI1_LSB;
            #else
            m_spi_master_ex_state = TEST_STATE_SPI0_LSB;
            #endif /* SPI_MASTER_1_ENABLE */

            break;
        #endif /* SPI_MASTER_0_ENABLE */

        #ifdef SPI_MASTER_1_ENABLE
        case TEST_STATE_SPI1_LSB:
            spi_master_init(SPI_MASTER_1, spi_master_1_event_handler, true);

            spi_send_recv(SPI_MASTER_1, m_tx_data_spi, m_rx_data_spi, TX_RX_MSG_LENGTH);
            m_spi_master_ex_state = TEST_STATE_SPI1_MSB;

            break;

        case TEST_STATE_SPI1_MSB:
            spi_master_init(SPI_MASTER_1, spi_master_1_event_handler, false);

            spi_send_recv(SPI_MASTER_1, m_tx_data_spi, m_rx_data_spi, TX_RX_MSG_LENGTH);

            #ifdef SPI_MASTER_0_ENABLE
            m_spi_master_ex_state = TEST_STATE_SPI0_LSB;
            #else
            m_spi_master_ex_state = TEST_STATE_SPI1_LSB;
            #endif /* SPI_MASTER_0_ENABLE */

            break;
        #endif /* SPI_MASTER_1_ENABLE */

        default:
            break;
    }
