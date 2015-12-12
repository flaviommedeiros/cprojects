switch (mode) {
		case mDNIe_UI_MODE:
#if 1 // QSEED Check save			
			if(isSetDMBMode==1)
			{
				mdp4_vg_qseed_init_VideoPlay(0);
//				mdp4_vg_qseed_init_VideoPlay(1);
				isSetDMBMode = 0;
			}
#endif			
			pLut = UI_LUT;
			sharpvalue = SHARPNESS_BYPASS;
			break;

		case mDNIe_VIDEO_MODE:
		case mDNIe_VIDEO_WARM_MODE:
		case mDNIe_VIDEO_COLD_MODE:
#if 1 // QSEED Check save			
			if(isSetDMBMode==1)
			{
				mdp4_vg_qseed_init_VideoPlay(0);
//				mdp4_vg_qseed_init_VideoPlay(1);
				isSetDMBMode = 0;
			}
#endif			
			pLut = VIDEO_LUT;
			sharpvalue = SHARPNESS_VIDEO;		
			break;

		case mDNIe_CAMERA_MODE:
			pLut = CAMERA_LUT;
			sharpvalue = SHARPNESS_BYPASS;
			break;

		case mDNIe_NAVI:
			pLut = NAVI_LUT;
			sharpvalue = SHARPNESS_BYPASS;
			break;
			
		case mDNIe_GALLERY:
			pLut = GALLERY_LUT;
			sharpvalue = SHARPNESS_BYPASS;
			break;
		case mDNIe_BYPASS: 
			pLut = BYPASS_LUT;
			sharpvalue = SHARPNESS_BYPASS;
			break;

#if defined(CONFIG_TDMB) || defined(CONFIG_TDMB_MODULE)
		case mDNIe_DMB_MODE:				// warm, clod not distinguish
		case mDNIe_DMB_WARM_MODE:
		case mDNIe_DMB_COLD_MODE:
#if 1  // QSEED Check save			
			if(isSetDMBMode==0)
			{
				mdp4_vg_qseed_init_DMB(0);
//				mdp4_vg_qseed_init_DMB(1);
				isSetDMBMode = 1;
			}
#endif			
			pLut = DMB_LUT;
			sharpvalue = SHARPNESS_DMB;
			break;
#endif 
#ifdef CONFIG_TARGET_LOCALE_NTT
		case mDNIe_ISDBT_MODE:
		case mDNIe_ISDBT_WARM_MODE:
		case mDNIe_ISDBT_COLD_MODE:
			pLut = BYPASS_LUT;
			sharpvalue = SHARPNESS_BYPASS;	
//			mDNIe_txtbuf_to_parsing(ISDBT_COLD_MODE_FILE);
			break;
#endif
#ifdef BROWSER_COLOR_TONE_SET
		case mDNIe_BROWSER_TONE1:
			pLut = BROWSER_TONE1_LUT;
			sharpvalue = SHARPNESS_BYPASS;
			break;
		case mDNIe_BROWSER_TONE2:
			pLut = BROWSER_TONE2_LUT;
			sharpvalue = SHARPNESS_BYPASS;
			break;
		case mDNIe_BROWSER_TONE3:
			pLut = BROWSER_TONE3_LUT;
			sharpvalue = SHARPNESS_BYPASS;
			break;			
#endif			
		}
