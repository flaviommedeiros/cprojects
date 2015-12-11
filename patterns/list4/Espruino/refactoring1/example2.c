if (!(jshADCInitialised&2)) {
        jshADCInitialised |= 2;
        needs_init = true;
        #if defined(STM32F3)
          RCC_AHBPeriphClockCmd( RCC_AHBPeriph_ADC12, ENABLE);
        #elif defined(STM32F4)
          RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2, ENABLE);
        #else
          RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2, ENABLE);
        #endif
      }
#endif
