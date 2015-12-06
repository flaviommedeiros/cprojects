#if USE_PLL_HSE_XTAL != 0
if (SetSysClock_PLL_HSE(0) == 0)
#endif
    {
      /* 3- If fail start with HSI or MSI clock */
#if (USE_PLL_HSI != 0)
      if (SetSysClock_PLL_HSI() == 0)
#else
      if (SetSysClock_PLL_MSI() == 0)
#endif
      {
        while(1)
        {
          // [TODO] Put something here to tell the user that a problem occured...
        }
      }
    }
