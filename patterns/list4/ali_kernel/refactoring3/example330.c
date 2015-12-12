switch(CRT2Index) {
	 case 10: LVDSData = SiS_Pr->SiS_LVDS320x240Data_1;    break;
	 case 14: LVDSData = SiS_Pr->SiS_LVDS320x240Data_2;    break;
	 case 12: LVDSData = SiS_Pr->SiS_LVDS640x480Data_1;    break;
	 case 16: LVDSData = SiS_Pr->SiS_LVDS800x600Data_1;    break;
	 case 18: LVDSData = SiS_Pr->SiS_LVDS1024x600Data_1;   break;
	 case 20: LVDSData = SiS_Pr->SiS_LVDS1024x768Data_1;   break;
#ifdef SIS300
	 case 80: LVDSData = SiS_Pr->SiS_LVDSBARCO1366Data_1;  break;
	 case 81: LVDSData = SiS_Pr->SiS_LVDSBARCO1366Data_2;  break;
	 case 82: LVDSData = SiS_Pr->SiS_LVDSBARCO1024Data_1;  break;
	 case 84: LVDSData = SiS_Pr->SiS_LVDS848x480Data_1;    break;
	 case 85: LVDSData = SiS_Pr->SiS_LVDS848x480Data_2;    break;
#endif
	 case 90: LVDSData = SiS_Pr->SiS_CHTVUNTSCData;        break;
	 case 91: LVDSData = SiS_Pr->SiS_CHTVONTSCData;        break;
	 case 92: LVDSData = SiS_Pr->SiS_CHTVUPALData;         break;
	 case 93: LVDSData = SiS_Pr->SiS_CHTVOPALData;         break;
	 case 94: LVDSData = SiS_Pr->SiS_CHTVUPALMData;        break;
	 case 95: LVDSData = SiS_Pr->SiS_CHTVOPALMData;        break;
	 case 96: LVDSData = SiS_Pr->SiS_CHTVUPALNData;        break;
	 case 97: LVDSData = SiS_Pr->SiS_CHTVOPALNData;        break;
	 case 99: LVDSData = SiS_Pr->SiS_CHTVSOPALData;	       break;
      }
