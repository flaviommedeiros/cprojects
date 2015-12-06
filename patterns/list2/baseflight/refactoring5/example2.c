#ifdef  PRINTF_LONG_SUPPORT
if (lng)
                        li2a(va_arg(va, unsigned long int), bf);
                    else
#endif
                        i2a(va_arg(va, int), bf);
