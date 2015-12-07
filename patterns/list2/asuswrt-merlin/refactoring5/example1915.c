#ifdef PCIX_TARGET_WORKAROUND
if (pDevice->Flags & UNDI_FIX_FLAG)
    {
        return (LM_RegRdInd(pDevice, Register));
    }
    else
#endif
    {
        return (REG_RD_OFFSET(pDevice, Register));
    }
