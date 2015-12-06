ONE_DESCRIPTOR DFU_String_Descriptor[6] =
#else
 ONE_DESCRIPTOR DFU_String_Descriptor[5] =
#endif
  {
    {       (uint8_t*)DFU_StringLangId,          DFU_SIZ_STRING_LANGID       },
    {       (uint8_t*)DFU_StringVendor,          DFU_SIZ_STRING_VENDOR       },
    {       (uint8_t*)DFU_StringProduct,         DFU_SIZ_STRING_PRODUCT      },
    {       (uint8_t*)DFU_StringSerial,          DFU_SIZ_STRING_SERIAL       },
    {       (uint8_t*)DFU_StringInterface0,      DFU_SIZ_STRING_INTERFACE0   }
#ifdef SPARK_SFLASH_ENABLE
    ,
    {       (uint8_t*)DFU_StringInterface1,      DFU_SIZ_STRING_INTERFACE1   }
#endif
  };
