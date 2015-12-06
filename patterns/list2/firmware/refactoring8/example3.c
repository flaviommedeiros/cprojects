const STM32_SPI_Info spiMap[TOTAL_SPI] =
{
        { SPI1, &RCC->APB2ENR, RCC_APB2Periph_SPI1, &RCC->AHB1ENR, RCC_AHB1Periph_DMA2, DMA_Channel_3,
          DMA2_Stream5, DMA2_Stream2, DMA2_Stream5_IRQn, DMA_IT_TCIF5, SCK, MISO, MOSI, SS, GPIO_AF_SPI1 },
        { SPI3, &RCC->APB1ENR, RCC_APB1Periph_SPI3, &RCC->AHB1ENR, RCC_AHB1Periph_DMA1, DMA_Channel_0,
          DMA1_Stream7, DMA1_Stream2, DMA1_Stream7_IRQn, DMA_IT_TCIF7, D4, D3, D2, D5, GPIO_AF_SPI3  }
#if PLATFORM_ID == 10 // Electron
        ,{ SPI3, &RCC->APB1ENR, RCC_APB1Periph_SPI3, &RCC->AHB1ENR, RCC_AHB1Periph_DMA1, DMA_Channel_0,
          DMA1_Stream7, DMA1_Stream2, DMA1_Stream7_IRQn, DMA_IT_TCIF7, C3, C2, C1, C0, GPIO_AF_SPI3  }
#endif
};
