#ifdef  PRINTF_LONG_SUPPORT
if (lng)
                        uli2a(va_arg(va, unsigned long int), 10, 0, bf);
                    else
#endif
                        ui2a(va_arg(va, unsigned int), 10, 0, bf);
