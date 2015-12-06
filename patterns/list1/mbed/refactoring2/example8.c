#if USE_PLL_HSE_XTAL != 0
if (SetSysClock_PLL_HSE(0) == 0)
    #endif
    {
      /* 3- If fail start with HSI clock */
      if (SetSysClock_PLL_HSI() == 0)
      {
        while(1)
        {
          // [TODO] Put something here to tell the user that a problem occured...
        }
      }
    }
