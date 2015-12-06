if ((CLOCK_HAL_GetClkStatMode(baseAddr) == kMcgClkStatInternalRef) &&  /* CLKS mux in internal ref clk (CLKST=1) */
             (CLOCK_HAL_GetInternalRefStatMode(baseAddr) == kMcgInternalRefStatInternal) && /* FLL ref is internal ref clk (IREFST=1) */
#if FSL_FEATURE_MCG_HAS_PLL                 
             (CLOCK_HAL_GetPllStatMode(baseAddr) == kMcgPllStatFll) &&   /* PLLS mux is FLL (PLLST=0) */
#endif               
             (CLOCK_HAL_GetLowPowerMode(baseAddr) == kMcgLowPowerSelNormal))  /* MCG_C2[LP] bit is not set (LP=0) */
    {  
        return kMcgModeFBI;                              /* return FBI code */
    }
    /* Check MCG is in FEE mode */
    else if ((CLOCK_HAL_GetClkStatMode(baseAddr) == kMcgClkStatFll) &&   /* CLKS mux is FLL output (CLKST=0) */
             (CLOCK_HAL_GetInternalRefStatMode(baseAddr) == kMcgInternalRefStatExternal) /* FLL ref is external ref clk (IREFST=0) */
#if FSL_FEATURE_MCG_HAS_PLL                 
          && (CLOCK_HAL_GetPllStatMode(baseAddr) == kMcgPllStatFll))
