#ifdef PCIX_TARGET_WORKAROUND
if (pDevice->Flags & ENABLE_PCIX_FIX_FLAG)
    {
        LM_RegWrInd(pDevice, Register, Value32);
    }
    else
#endif
    {
        LM_UINT32 dummy;

        REG_WR_OFFSET(pDevice, Register, Value32);
        if (ReadBack && (pDevice->Flags & REG_RD_BACK_FLAG))
        {
            dummy = REG_RD_OFFSET(pDevice, Register);
        }
    }
