switch (dev->id) {
		case 1:
			fp_vsCSD = 0;
			break;

		case 5:
			fp_vsGPS = 0;
			break;

		case 6:
			fp_vsEXGPS = 0;
			break;

      	case 8 : 
         	fp_vsEFS = 0;
         	break;

		case 25 : 
         	fp_vsSMD = 0;
         	break; 

#ifdef CONFIG_ENABLE_TTY_CIQ
      	case 9 :
         	fp_vsCIQ1 = 0;
         	break;

      	case 26 :
         	fp_vsCIQ0 = 0;
         	break;
#endif
			
		default:
			break;
}
