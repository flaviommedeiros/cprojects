#ifdef INCLUDE_TBI_SUPPORT
if (pDevice->TbiFlags & ENABLE_TBI_FLAG)
    {
        LmStatus = LM_SetupFiberPhy(pDevice);
    }
    else
#endif /* INCLUDE_TBI_SUPPORT */
    {
        LmStatus = LM_SetupCopperPhy(pDevice);
    }
