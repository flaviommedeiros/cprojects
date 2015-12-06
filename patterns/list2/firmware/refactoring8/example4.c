STM32_USART_Info USART_MAP[TOTAL_USARTS] =
{
		/*
		 * USART_peripheral (USARTx/UARTx; not using others)
		 * clock control register (APBxENR)
		 * clock enable bit value (RCC_APBxPeriph_USARTx/RCC_APBxPeriph_UARTx)
		 * interrupt number (USARTx_IRQn/UARTx_IRQn)
		 * TX pin
		 * RX pin
		 * TX pin source
		 * RX pin source
		 * GPIO AF map (GPIO_AF_USARTx/GPIO_AF_UARTx)
		 * <tx_buffer pointer> used internally and does not appear below
		 * <rx_buffer pointer> used internally and does not appear below
		 * <usart enabled> used internally and does not appear below
		 * <usart transmitting> used internally and does not appear below
		 */
		{ USART1, &RCC->APB2ENR, RCC_APB2Periph_USART1, USART1_IRQn, TX, RX, GPIO_PinSource9, GPIO_PinSource10, GPIO_AF_USART1 }, // USART 1
		{ USART2, &RCC->APB1ENR, RCC_APB1Periph_USART2, USART2_IRQn, RGBG, RGBB, GPIO_PinSource2, GPIO_PinSource3, GPIO_AF_USART2 } // USART 2
#if PLATFORM_ID == 10 // Electron
		,{ USART3, &RCC->APB1ENR, RCC_APB1Periph_USART3, USART3_IRQn, TXD_UC, RXD_UC, GPIO_PinSource10, GPIO_PinSource11, GPIO_AF_USART3 } // USART 3
        ,{ UART4, &RCC->APB1ENR, RCC_APB1Periph_UART4, UART4_IRQn, C3, C2, GPIO_PinSource10, GPIO_PinSource11, GPIO_AF_UART4 } // UART 4
        ,{ UART5, &RCC->APB1ENR, RCC_APB1Periph_UART5, UART5_IRQn, C1, C0, GPIO_PinSource12, GPIO_PinSource2, GPIO_AF_UART5 } // UART 5
#endif
};
