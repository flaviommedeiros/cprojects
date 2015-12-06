switch (Type)
	{
		#ifndef IL_NO_TGA
		case IL_TGA:
			return ilIsValidTga(FileName);
		#endif

		#ifndef IL_NO_JPG
		case IL_JPG:
			return ilIsValidJpeg(FileName);
		#endif

		#ifndef IL_NO_DDS
		case IL_DDS:
			return ilIsValidDds(FileName);
		#endif

		#ifndef IL_NO_PNG
		case IL_PNG:
			return ilIsValidPng(FileName);
		#endif

		#ifndef IL_NO_BMP
		case IL_BMP:
			return ilIsValidBmp(FileName);
		#endif

		#ifndef IL_NO_DICOM
		case IL_DICOM:
			return ilIsValidDicom(FileName);
		#endif

		#ifndef IL_NO_EXR
		case IL_EXR:
			return ilIsValidExr(FileName);
		#endif

		#ifndef IL_NO_GIF
		case IL_GIF:
			return ilIsValidGif(FileName);
		#endif

		#ifndef IL_NO_HDR
		case IL_HDR:
			return ilIsValidHdr(FileName);
		#endif

		#ifndef IL_NO_ICNS
		case IL_ICNS:
			return ilIsValidIcns(FileName);
		#endif

		#ifndef IL_NO_IWI
		case IL_IWI:
			return ilIsValidIwi(FileName);
		#endif

    	#ifndef IL_NO_ILBM
        case IL_ILBM:
            return ilIsValidIlbm(FileName);
	    #endif

		#ifndef IL_NO_JP2
		case IL_JP2:
			return ilIsValidJp2(FileName);
		#endif

		#ifndef IL_NO_LIF
		case IL_LIF:
			return ilIsValidLif(FileName);
		#endif

		#ifndef IL_NO_MDL
		case IL_MDL:
			return ilIsValidMdl(FileName);
		#endif

		#ifndef IL_NO_MP3
		case IL_MP3:
			return ilIsValidMp3(FileName);
		#endif

		#ifndef IL_NO_PCX
		case IL_PCX:
			return ilIsValidPcx(FileName);
		#endif

		#ifndef IL_NO_PIC
		case IL_PIC:
			return ilIsValidPic(FileName);
		#endif

		#ifndef IL_NO_PNM
		case IL_PNM:
			return ilIsValidPnm(FileName);
		#endif

		#ifndef IL_NO_PSD
		case IL_PSD:
			return ilIsValidPsd(FileName);
		#endif

		#ifndef IL_NO_PSP
		case IL_PSP:
			return ilIsValidPsp(FileName);
		#endif

		#ifndef IL_NO_SGI
		case IL_SGI:
			return ilIsValidSgi(FileName);
		#endif

		#ifndef IL_NO_SUN
		case IL_SUN:
			return ilIsValidSun(FileName);
		#endif

		#ifndef IL_NO_TIF
		case IL_TIF:
			return ilIsValidTiff(FileName);
		#endif

		#ifndef IL_NO_TPL
		case IL_TPL:
			return ilIsValidTpl(FileName);
		#endif

		#ifndef IL_NO_VTF
		case IL_VTF:
			return ilIsValidVtf(FileName);
		#endif

		#ifndef IL_NO_XPM
		case IL_XPM:
			return ilIsValidXpm(FileName);
		#endif
	}
