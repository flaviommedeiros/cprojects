switch (dev->id) {
		case 1:
			fp_vsCSD = 1;
			break;

		case 5:
			fp_vsGPS = 1;
			break;

		case 6:
			fp_vsEXGPS = 1;
			break;

      	case 8 : 
         	fp_vsEFS = 1;
        	break; 

      	case 25 : 
         	fp_vsSMD = 1;
         	break; 

#ifdef CONFIG_ENABLE_TTY_CIQ
      	case 9 :
         	fp_vsCIQ1 = 1;
         	break;

      	case 26 :
         	fp_vsCIQ0 = 1;
         	break;
#endif
		default:
			break;
	}
