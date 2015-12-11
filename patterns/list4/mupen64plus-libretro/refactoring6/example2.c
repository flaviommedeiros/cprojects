if(itype[i]==LOAD || itype[i]==LOADLR || itype[i]==STORE || itype[i]==STORELR || itype[i]==C1LS
#ifdef EMU_PCSXR
        || itype[i]==C2LS
#endif
        )
    hsn[TLREG]=0;
