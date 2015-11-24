if ((CLOCK_HAL_GetClkStatMode(baseAddr) == kMcgClkStatPll) &&   /* CLKS mux is PLL output (CLKST=3) */
             (CLOCK_HAL_GetInternalRefStatMode(baseAddr) == kMcgInternalRefStatExternal)  /* FLL ref is external ref clk (IREFST=0) */
#if FSL_FEATURE_MCG_HAS_PLL                    
         && (CLOCK_HAL_GetPllStatMode(baseAddr) == kMcgPllStatPllClkSel))
