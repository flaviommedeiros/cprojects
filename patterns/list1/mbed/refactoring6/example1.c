if ((CLOCK_HAL_GetClkStatMode(baseAddr) == kMcgClkStatFll) &&        /* CLKS mux is FLL output (CLKST=0) */
        (CLOCK_HAL_GetInternalRefStatMode(baseAddr) == kMcgInternalRefStatInternal)      /* FLL ref is internal ref clk (IREFST=1) */
#if FSL_FEATURE_MCG_HAS_PLL          
        && (CLOCK_HAL_GetPllStatMode(baseAddr) == kMcgPllStatFll))
