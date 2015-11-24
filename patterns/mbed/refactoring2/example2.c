#if FSL_FEATURE_MCG_HAS_PLL1
if (pllcsSelect == kMcgPllcsSelectPll0)
#endif
    {
        /* 
         * Configure MCG_C5
         * If the PLL is to run in STOP mode then the PLLSTEN bit needs 
         * to be OR'ed in here or in user code.       
         */

        CLOCK_HAL_SetPllExternalRefDivider0(baseAddr, prdivVal - 1);

        /* 
         * Configure MCG_C6
         * The PLLS bit is set to enable the PLL, MCGOUT still sourced from ext ref clk 
         * The clock monitor is not enabled here as it has likely been enabled previously and 
         * so the value of CME is not altered here.
         * The loss of lock interrupt can be enabled by seperate OR'ing in the LOLIE bit in MCG_C6
         */

        CLOCK_HAL_SetVoltCtrlOscDivider0(baseAddr, vdivVal - FSL_FEATURE_MCG_PLL_VDIV_BASE);
        CLOCK_HAL_SetPllSelMode(baseAddr, kMcgPllSelPllClkSel);

        /* Set LP bit to enable the PLL */
        CLOCK_HAL_SetLowPowerMode(baseAddr, kMcgLowPowerSelNormal);

        // wait for PLLST status bit to set
        for (i = 0 ; i < kMcgConstant2000 ; i++)
        {
            if (CLOCK_HAL_GetPllStatMode(baseAddr) == kMcgPllStatPllClkSel)
            {
                /* jump out early if PLLST sets before loop finishes */
                break;
            }
        }

        /* check bit is really set  */
        if ((CLOCK_HAL_GetPllStatMode(baseAddr) != kMcgPllStatPllClkSel))
        {
            /* return with error if not set */
            return kMcgErrPllstSetTimeout;
        }

        /* Wait for LOCK bit to set */
        for (i = 0 ; i < kMcgConstant2000 ; i++)
        {
            if (CLOCK_HAL_GetLock0Mode(baseAddr) ==  kMcgLockLocked)
            {
                /* jump out early if LOCK sets before loop finishes */
                break;
            }
        }

        /* check bit is really set */
        if ((CLOCK_HAL_GetLock0Mode(baseAddr) !=  kMcgLockLocked))
        {
            /* return with error if not set */
            return kMcgErrPllLockBit;
        }
    
#if FSL_FEATURE_MCG_USE_PLLREFSEL
        /* wait for PLLCST status bit to clear */
        for (i = 0 ; i < kMcgConstant2000 ; i++)
        {
            if (CLOCK_HAL_GetPllcst(baseAddr) == kMcgPllcsSelectPll0)
            {
                /* jump out early if PLLST sets before loop finishes */
                break;
            }
        }

        /* check bit is really set */
        if (CLOCK_HAL_GetPllcst(baseAddr) != kMcgPllcsSelectPll0)
        {
            /* return with error if not set */
            return kMcgErrPllcst;
        }
#endif        
    }
#if FSL_FEATURE_MCG_HAS_PLL1
    else
    {
        /*
         * Configure MCG_C11
         * If the PLL is to run in STOP mode 
         * then the PLLSTEN bit needs to be OR'ed in here or in user code.       
         */
        CLOCK_HAL_SetPrdiv1(prdivVal - 1);

        /* 
         * Configure MCG_C12
         * The PLLS bit is set to enable the PLL, MCGOUT still sourced from ext ref clk 
         * The clock monitor is not enabled here as it has likely been enabled previously
         * and so the value of CME is not altered here.
         * The loss of lock interrupt can be enabled by seperate OR'ing in the LOLIE bit 
         * in MCG_C12
         */

        CLOCK_HAL_SetVdiv1(vdivVal - FSL_FEATURE_MCG_PLL_VDIV_BASE);
        CLOCK_HAL_SetPllSelMode(kMcgPllSelPllClkSel);

        /* Set LP bit to enable the PLL */
        CLOCK_HAL_SetLowPowerMode(kMcgLowPowerSelNormal);

        // wait for PLLST status bit to set
        for (i = 0 ; i < kMcgConstant2000 ; i++)
        {
            if (CLOCK_HAL_GetPllStatMode(baseAddr) == kMcgPllStatPllClkSel)
            {
                /* jump out early if PLLST sets before loop finishes */
                break;
            }
        }

        /* check bit is really set  */
        if ((CLOCK_HAL_GetPllStatMode(baseAddr) != kMcgPllStatPllClkSel))
        {
            /* return with error if not set */
            return kMcgErrPllstSetTimeout;
        }

        /* Wait for LOCK bit to set */
        for (i = 0 ; i < kMcgConstant2000 ; i++)
        {
            if (CLOCK_HAL_GetLock1(baseAddr) ==  kMcgLockLocked)
            {
                /* jump out early if LOCK sets before loop finishes */
                break;
            }
        }

        /* check bit is really set */
        if ((CLOCK_HAL_GetLock1(baseAddr) !=  kMcgLockLocked))
        {
            /* return with error if not set */
            return kMcgErrPllLockBit;
        }
   
        /* wait for PLLCST status bit to clear */
        for (i = 0 ; i < kMcgConstant2000 ; i++)
        {
            if (CLOCK_HAL_GetPllcst(baseAddr) == kMcgPllcsSelectPll1)
            {
                /* jump out early if PLLST sets before loop finishes */
                break;
            }
        }

        /* check bit is really set */
        if (CLOCK_HAL_GetPllcst(baseAddr) != kMcgPllcsSelectPll1)
        {
            /* return with error if not set */
            return kMcgErrPllcst;
        }
    }
