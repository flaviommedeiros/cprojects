#ifdef CONFIG_FB_SIS_315
if(SiS_GetCRT2Part2Ptr(SiS_Pr, ModeNo, ModeIdIndex, RefreshRateTableIndex,
                          			&CRT2Index, &resindex)) {
      switch(CRT2Index) {
        case 206: CRT2Part2Ptr = SiS310_CRT2Part2_Asus1024x768_3;    break;
	default:
        case 200: CRT2Part2Ptr = SiS_Pr->SiS_CRT2Part2_1024x768_1;   break;
      }

      SiS_SetRegANDOR(SiS_Pr->SiS_Part2Port,0x01,0x80,(CRT2Part2Ptr+resindex)->CR[0]);
      SiS_SetRegANDOR(SiS_Pr->SiS_Part2Port,0x02,0x80,(CRT2Part2Ptr+resindex)->CR[1]);
      for(i = 2, j = 0x04; j <= 0x06; i++, j++ ) {
        SiS_SetReg(SiS_Pr->SiS_Part2Port,j,(CRT2Part2Ptr+resindex)->CR[i]);
      }
      for(j = 0x1c; j <= 0x1d; i++, j++ ) {
        SiS_SetReg(SiS_Pr->SiS_Part2Port,j,(CRT2Part2Ptr+resindex)->CR[i]);
      }
      for(j = 0x1f; j <= 0x21; i++, j++ ) {
        SiS_SetReg(SiS_Pr->SiS_Part2Port,j,(CRT2Part2Ptr+resindex)->CR[i]);
      }
      SiS_SetReg(SiS_Pr->SiS_Part2Port,0x23,(CRT2Part2Ptr+resindex)->CR[10]);
      SiS_SetRegANDOR(SiS_Pr->SiS_Part2Port,0x25,0x0f,(CRT2Part2Ptr+resindex)->CR[11]);

      SiS_SetGroup2_Tail(SiS_Pr, ModeNo);

  } else {
#endif

    /* Checked for 1024x768, 1280x1024, 1400x1050, 1600x1200 */
    /*             Clevo dual-link 1024x768 */
    /* 		   Compaq 1280x1024 has HT 1696 sometimes (calculation OK, if given HT is correct)  */
    /*		   Acer: OK, but uses different setting for VESA timing at 640/800/1024 and 640x400 */

    if(SiS_Pr->SiS_LCDInfo & DontExpandLCD) {
       if((SiS_Pr->SiS_LCDInfo & LCDPass11) || (SiS_Pr->PanelYRes == SiS_Pr->SiS_VDE)) {
          tempbx = SiS_Pr->SiS_VDE - 1;
          tempcx = SiS_Pr->SiS_VT - 1;
       } else {
          tempbx = SiS_Pr->SiS_VDE + ((SiS_Pr->PanelYRes - SiS_Pr->SiS_VDE) / 2);
	  tempcx = SiS_Pr->SiS_VT - ((SiS_Pr->PanelYRes - SiS_Pr->SiS_VDE) / 2);
       }
    } else {
       tempbx = SiS_Pr->PanelYRes;
       tempcx = SiS_Pr->SiS_VT;
       tempax = 1;
       if(SiS_Pr->PanelYRes != SiS_Pr->SiS_VDE) {
          tempax = SiS_Pr->PanelYRes;
	  /* if(SiS_Pr->SiS_VGAVDE == 525) tempax += 0x3c;   */  /* 651+301C */
          if(SiS_Pr->PanelYRes < SiS_Pr->SiS_VDE) {
             tempax = tempcx = 0;
          } else {
             tempax -= SiS_Pr->SiS_VDE;
          }
          tempax >>= 1;
       }
       tempcx -= tempax; /* lcdvdes */
       tempbx -= tempax; /* lcdvdee */
    }

    /* Non-expanding: lcdvdes = tempcx = VT-1; lcdvdee = tempbx = VDE-1 */

    SiS_SetReg(SiS_Pr->SiS_Part2Port,0x05,tempcx);	/* lcdvdes  */
    SiS_SetReg(SiS_Pr->SiS_Part2Port,0x06,tempbx);	/* lcdvdee  */

    temp = (tempbx >> 5) & 0x38;
    temp |= ((tempcx >> 8) & 0x07);
    SiS_SetReg(SiS_Pr->SiS_Part2Port,0x02,temp);

    tempax = SiS_Pr->SiS_VDE;
    if((SiS_Pr->SiS_LCDInfo & DontExpandLCD) && (!(SiS_Pr->SiS_LCDInfo & LCDPass11))) {
       tempax = SiS_Pr->PanelYRes;
    }
    tempcx = (SiS_Pr->SiS_VT - tempax) >> 4;
    if((SiS_Pr->SiS_LCDInfo & DontExpandLCD) && (!(SiS_Pr->SiS_LCDInfo & LCDPass11))) {
       if(SiS_Pr->PanelYRes != SiS_Pr->SiS_VDE) {
	  tempcx = (SiS_Pr->SiS_VT - tempax) / 10;
       }
    }

    tempbx = ((SiS_Pr->SiS_VT + SiS_Pr->SiS_VDE) >> 1) - 1;
    if(SiS_Pr->SiS_LCDInfo & DontExpandLCD) {
       if(SiS_Pr->PanelYRes != SiS_Pr->SiS_VDE) {
          if(!(SiS_Pr->SiS_LCDInfo & LCDPass11)) { /* ? */
             tempax = SiS_Pr->SiS_VT - SiS_Pr->PanelYRes;
	     if(tempax % 4) { tempax >>= 2; tempax++; }
	     else           { tempax >>= 2;           }
             tempbx -= (tempax - 1);
	  } else {
	     tempbx -= 10;
	     if(tempbx <= SiS_Pr->SiS_VDE) tempbx = SiS_Pr->SiS_VDE + 1;
	  }
       }
    }
    if(SiS_Pr->SiS_LCDResInfo == Panel_1024x768) {
       tempbx++;
       if((!(SiS_Pr->SiS_LCDInfo & DontExpandLCD)) || (crt2crtc == 6)) {
          if(SiS_Pr->SiS_SetFlag & LCDVESATiming) {
	     tempbx = 770;
	     tempcx = 3;
	  }
       }
    }

    /* non-expanding: lcdvrs = ((VT + VDE) / 2) - 10 */

    if(SiS_Pr->UseCustomMode) {
       tempbx = SiS_Pr->CVSyncStart;
    }

    SiS_SetReg(SiS_Pr->SiS_Part2Port,0x04,tempbx);	    /* lcdvrs */

    temp = (tempbx >> 4) & 0xF0;
    tempbx += (tempcx + 1);
    temp |= (tempbx & 0x0F);

    if(SiS_Pr->UseCustomMode) {
       temp &= 0xf0;
       temp |= (SiS_Pr->CVSyncEnd & 0x0f);
    }

    SiS_SetReg(SiS_Pr->SiS_Part2Port,0x01,temp);

#ifdef CONFIG_FB_SIS_300
    SiS_Group2LCDSpecial(SiS_Pr, ModeNo, crt2crtc);
#endif

    bridgeoffset = 7;
    if(SiS_Pr->SiS_VBType & VB_SIS30xBLV)	bridgeoffset += 2;
    if(SiS_Pr->SiS_VBType & VB_SIS30xCLV)	bridgeoffset += 2; /* OK for Averatec 1280x800 (301C) */
    if(SiS_IsDualLink(SiS_Pr))			bridgeoffset++;
    else if(SiS_Pr->SiS_VBType & VB_SIS302LV)	bridgeoffset++;    /* OK for Asus A4L 1280x800 */
    /* Higher bridgeoffset shifts to the LEFT */

    temp = 0;
    if((SiS_Pr->SiS_LCDInfo & DontExpandLCD) && (!(SiS_Pr->SiS_LCDInfo & LCDPass11))) {
       if(SiS_Pr->PanelXRes != SiS_Pr->SiS_HDE) {
	  temp = SiS_Pr->SiS_HT - ((SiS_Pr->PanelXRes - SiS_Pr->SiS_HDE) / 2);
	  if(SiS_IsDualLink(SiS_Pr)) temp >>= 1;
       }
    }
    temp += bridgeoffset;
    SiS_SetReg(SiS_Pr->SiS_Part2Port,0x1F,temp);  	     /* lcdhdes */
    SiS_SetRegANDOR(SiS_Pr->SiS_Part2Port,0x20,0x0F,((temp >> 4) & 0xf0));

    tempcx = SiS_Pr->SiS_HT;
    tempax = tempbx = SiS_Pr->SiS_HDE;
    if((SiS_Pr->SiS_LCDInfo & DontExpandLCD) && (!(SiS_Pr->SiS_LCDInfo & LCDPass11))) {
       if(SiS_Pr->PanelXRes != SiS_Pr->SiS_HDE) {
          tempax = SiS_Pr->PanelXRes;
          tempbx = SiS_Pr->PanelXRes - ((SiS_Pr->PanelXRes - SiS_Pr->SiS_HDE) / 2);
       }
    }
    if(SiS_IsDualLink(SiS_Pr)) {
       tempcx >>= 1;
       tempbx >>= 1;
       tempax >>= 1;
    }

    tempbx += bridgeoffset;

    SiS_SetReg(SiS_Pr->SiS_Part2Port,0x23,tempbx);	    /* lcdhdee */
    SiS_SetRegANDOR(SiS_Pr->SiS_Part2Port,0x25,0xF0,((tempbx >> 8) & 0x0f));

    tempcx = (tempcx - tempax) >> 2;

    tempbx += tempcx;
    push2 = tempbx;

    if(SiS_Pr->SiS_LCDResInfo == Panel_1280x1024) {
       if(SiS_Pr->SiS_LCDInfo & DontExpandLCD) {
          if(SiS_Pr->SiS_LCDInfo & LCDPass11) {
             if(SiS_Pr->SiS_HDE == 1280) tempbx = (tempbx & 0xff00) | 0x47;
	  }
       }
    }

    if(SiS_Pr->UseCustomMode) {
       tempbx = SiS_Pr->CHSyncStart;
       if(modeflag & HalfDCLK) tempbx <<= 1;
       if(SiS_IsDualLink(SiS_Pr)) tempbx >>= 1;
       tempbx += bridgeoffset;
    }

    SiS_SetReg(SiS_Pr->SiS_Part2Port,0x1C,tempbx);	    /* lcdhrs */
    SiS_SetRegANDOR(SiS_Pr->SiS_Part2Port,0x1D,0x0F,((tempbx >> 4) & 0xf0));

    tempbx = push2;

    tempcx <<= 1;
    if((SiS_Pr->SiS_LCDInfo & DontExpandLCD) && (!(SiS_Pr->SiS_LCDInfo & LCDPass11))) {
       if(SiS_Pr->PanelXRes != SiS_Pr->SiS_HDE) tempcx >>= 2;
    }
    tempbx += tempcx;

    if(SiS_Pr->UseCustomMode) {
       tempbx = SiS_Pr->CHSyncEnd;
       if(modeflag & HalfDCLK) tempbx <<= 1;
       if(SiS_IsDualLink(SiS_Pr)) tempbx >>= 1;
       tempbx += bridgeoffset;
    }

    SiS_SetReg(SiS_Pr->SiS_Part2Port,0x21,tempbx);	    /* lcdhre */

    SiS_SetGroup2_Tail(SiS_Pr, ModeNo);

#ifdef CONFIG_FB_SIS_300
    SiS_Set300Part2Regs(SiS_Pr, ModeIdIndex, RefreshRateTableIndex, ModeNo);
#endif
#ifdef CONFIG_FB_SIS_315
  }
