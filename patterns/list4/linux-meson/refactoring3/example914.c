switch(SiS_Pr->ChipType) {
#ifdef CONFIG_FB_SIS_300
   case SIS_300:
      SiS_SetCRT1FIFO_300(SiS_Pr, ModeNo, RefreshRateTableIndex);
      break;
   case SIS_540:
   case SIS_630:
   case SIS_730:
      SiS_SetCRT1FIFO_630(SiS_Pr, ModeNo, RefreshRateTableIndex);
      break;
#endif
   default:
#ifdef CONFIG_FB_SIS_315
      if(SiS_Pr->ChipType == XGI_20) {
         unsigned char sr2b = 0, sr2c = 0;
         switch(ModeNo) {
	 case 0x00:
	 case 0x01: sr2b = 0x4e; sr2c = 0xe9; break;
	 case 0x04:
	 case 0x05:
	 case 0x0d: sr2b = 0x1b; sr2c = 0xe3; break;
	 }
	 if(sr2b) {
            SiS_SetReg(SiS_Pr->SiS_P3c4,0x2b,sr2b);
	    SiS_SetReg(SiS_Pr->SiS_P3c4,0x2c,sr2c);
	    SiS_SetRegByte(SiS_Pr->SiS_P3c2,(SiS_GetRegByte(SiS_Pr->SiS_P3cc) | 0x0c));
	 }
      }
      SiS_SetCRT1FIFO_310(SiS_Pr, ModeNo, ModeIdIndex);
#endif
      break;
   }
