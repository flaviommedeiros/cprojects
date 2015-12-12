#if STM32_F3_LINE == STM32_F3_LINE_303
if ( (dev == ADC1) || (dev == ADC3) )
#else
		if (dev == ADC1)
#endif
			adc_init(dev);
