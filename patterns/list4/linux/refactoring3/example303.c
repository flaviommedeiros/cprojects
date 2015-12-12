switch(CRT2Index) {
	      case Panel_1024x768      : LCDPtr = SiS_Pr->SiS_ExtLCD1024x768Data;   break;
	      case Panel_1024x768  + 32: LCDPtr = SiS_Pr->SiS_St2LCD1024x768Data;   break;
	      case Panel_1280x720      :
	      case Panel_1280x720  + 32: LCDPtr = SiS_Pr->SiS_LCD1280x720Data;      break;
	      case Panel_1280x768_2    : LCDPtr = SiS_Pr->SiS_ExtLCD1280x768_2Data; break;
	      case Panel_1280x768_2+ 32: LCDPtr = SiS_Pr->SiS_StLCD1280x768_2Data;  break;
	      case Panel_1280x800      :
	      case Panel_1280x800  + 32: LCDPtr = SiS_Pr->SiS_LCD1280x800Data;      break;
	      case Panel_1280x800_2    :
	      case Panel_1280x800_2+ 32: LCDPtr = SiS_Pr->SiS_LCD1280x800_2Data;    break;
	      case Panel_1280x854      :
	      case Panel_1280x854  + 32: LCDPtr = SiS_Pr->SiS_LCD1280x854Data;      break;
	      case Panel_1280x960      :
	      case Panel_1280x960  + 32: LCDPtr = SiS_Pr->SiS_LCD1280x960Data;      break;
	      case Panel_1280x1024     : LCDPtr = SiS_Pr->SiS_ExtLCD1280x1024Data;  break;
	      case Panel_1280x1024 + 32: LCDPtr = SiS_Pr->SiS_St2LCD1280x1024Data;  break;
	      case Panel_1400x1050     : LCDPtr = SiS_Pr->SiS_ExtLCD1400x1050Data;  break;
	      case Panel_1400x1050 + 32: LCDPtr = SiS_Pr->SiS_StLCD1400x1050Data;   break;
	      case Panel_1600x1200     : LCDPtr = SiS_Pr->SiS_ExtLCD1600x1200Data;  break;
	      case Panel_1600x1200 + 32: LCDPtr = SiS_Pr->SiS_StLCD1600x1200Data;   break;
	      case Panel_1680x1050     :
	      case Panel_1680x1050 + 32: LCDPtr = SiS_Pr->SiS_LCD1680x1050Data;     break;
	      case 100		       : LCDPtr = SiS_Pr->SiS_NoScaleData;	    break;
#ifdef CONFIG_FB_SIS_315
	      case 200                 : LCDPtr = SiS310_ExtCompaq1280x1024Data;    break;
	      case 201                 : LCDPtr = SiS_Pr->SiS_St2LCD1280x1024Data;  break;
#endif
	      default                  : LCDPtr = SiS_Pr->SiS_ExtLCD1024x768Data;   break;
	   }
