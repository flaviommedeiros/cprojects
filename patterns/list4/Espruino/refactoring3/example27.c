switch (analog & JSH_MASK_ANALOG_CH) {
#ifndef STM32F3XX
  case JSH_ANALOG_CH0  : return ADC_Channel_0;
#endif
  case JSH_ANALOG_CH1  : return ADC_Channel_1;
  case JSH_ANALOG_CH2  : return ADC_Channel_2;
  case JSH_ANALOG_CH3  : return ADC_Channel_3;
  case JSH_ANALOG_CH4  : return ADC_Channel_4;
  case JSH_ANALOG_CH5  : return ADC_Channel_5;
  case JSH_ANALOG_CH6  : return ADC_Channel_6;
  case JSH_ANALOG_CH7  : return ADC_Channel_7;
  case JSH_ANALOG_CH8  : return ADC_Channel_8;
  case JSH_ANALOG_CH9  : return ADC_Channel_9;
  case JSH_ANALOG_CH10  : return ADC_Channel_10;
  case JSH_ANALOG_CH11  : return ADC_Channel_11;
  case JSH_ANALOG_CH12  : return ADC_Channel_12;
  case JSH_ANALOG_CH13  : return ADC_Channel_13;
  case JSH_ANALOG_CH14  : return ADC_Channel_14;
  case JSH_ANALOG_CH15  : return ADC_Channel_15;
  case JSH_ANALOG_CH16  : return ADC_Channel_16;
  case JSH_ANALOG_CH17  : return ADC_Channel_17;
  default: jsExceptionHere(JSET_INTERNALERROR, "stmADCChannel"); return 0;
  }
