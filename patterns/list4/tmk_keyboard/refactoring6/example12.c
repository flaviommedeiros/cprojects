if ((CLOCK_HAL_GetClkStatMode(baseAddr) == kMcgClkStatFll) &&   /* CLKS mux is FLL output (CLKST=0) */
             (CLOCK_HAL_GetInternalRefStatMode(baseAddr) == kMcgInternalRefStatExternal) /* FLL ref is external ref clk (IREFST=0) */
#if FSL_FEATURE_MCG_HAS_PLL                 
          && (CLOCK_HAL_GetPllStatMode(baseAddr) == kMcgPllStatFll))
