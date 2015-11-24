if ((CLOCK_HAL_GetRange0Mode(baseAddr) != kMcgFreqRangeSelLow) 
#if FSL_FEATURE_MCG_USE_OSCSEL          /* case 1: use oscsel for ffclk      */
            && (CLOCK_HAL_GetOscselMode(baseAddr) != kMcgOscselRtc))
