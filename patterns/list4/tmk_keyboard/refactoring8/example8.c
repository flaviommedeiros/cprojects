static const uint8_t SPIMaskFromSCKDuration[] PROGMEM =
{
#if (F_CPU == 8000000)
	SPI_SPEED_FCPU_DIV_2,    // AVRStudio =   8MHz SPI, Actual =   4MHz SPI
	SPI_SPEED_FCPU_DIV_2,    // AVRStudio =   4MHz SPI, Actual =   4MHz SPI
	SPI_SPEED_FCPU_DIV_4,    // AVRStudio =   2MHz SPI, Actual =   2MHz SPI
	SPI_SPEED_FCPU_DIV_8,    // AVRStudio =   1MHz SPI, Actual =   1MHz SPI
	SPI_SPEED_FCPU_DIV_16,   // AVRStudio = 500KHz SPI, Actual = 500KHz SPI
	SPI_SPEED_FCPU_DIV_32,   // AVRStudio = 250KHz SPI, Actual = 250KHz SPI
	SPI_SPEED_FCPU_DIV_64,   // AVRStudio = 125KHz SPI, Actual = 125KHz SPI
#elif (F_CPU == 16000000)
	SPI_SPEED_FCPU_DIV_2,    // AVRStudio =   8MHz SPI, Actual =   8MHz SPI
	SPI_SPEED_FCPU_DIV_4,    // AVRStudio =   4MHz SPI, Actual =   4MHz SPI
	SPI_SPEED_FCPU_DIV_8,    // AVRStudio =   2MHz SPI, Actual =   2MHz SPI
	SPI_SPEED_FCPU_DIV_16,   // AVRStudio =   1MHz SPI, Actual =   1MHz SPI
	SPI_SPEED_FCPU_DIV_32,   // AVRStudio = 500KHz SPI, Actual = 500KHz SPI
	SPI_SPEED_FCPU_DIV_64,   // AVRStudio = 250KHz SPI, Actual = 250KHz SPI
	SPI_SPEED_FCPU_DIV_128   // AVRStudio = 125KHz SPI, Actual = 125KHz SPI
#else
	#error No SPI prescaler masks for chosen F_CPU speed.
#endif
};
