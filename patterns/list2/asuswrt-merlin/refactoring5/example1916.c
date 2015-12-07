#ifdef PCIX_TARGET_WORKAROUND
if (pDevice->Flags & ENABLE_PCIX_FIX_FLAG)
    {
        return;
    }
    else
#endif
    {
        if (pDevice->Flags & REG_RD_BACK_FLAG)
            return;

        dummy = REG_RD_OFFSET(pDevice, Register);
    }
