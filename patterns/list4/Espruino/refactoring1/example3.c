if (!(jshADCInitialised&4)) {
        jshADCInitialised |= 4;
        needs_init = true;
        #if defined(STM32F3)
          RCC_AHBPeriphClockCmd( RCC_AHBPeriph_ADC34, ENABLE);
        #elif defined(STM32F4)
          RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3, ENABLE);
        #else
          RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3, ENABLE);
        #endif
      }
#endif
