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
