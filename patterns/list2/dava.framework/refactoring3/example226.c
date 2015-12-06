switch (Type)
	{
		#ifndef IL_NO_TGA
		case IL_TGA:
			return ilIsValidTgaF(File);
		#endif

		#ifndef IL_NO_JPG
		case IL_JPG:
			return ilIsValidJpegF(File);
		#endif

		#ifndef IL_NO_DDS
		case IL_DDS:
			return ilIsValidDdsF(File);
		#endif

		#ifndef IL_NO_PNG
		case IL_PNG:
			return ilIsValidPngF(File);
		#endif

		#ifndef IL_NO_BMP
		case IL_BMP:
			return ilIsValidBmpF(File);
		#endif

		#ifndef IL_NO_DICOM
		case IL_DICOM:
			return ilIsValidDicomF(File);
		#endif

		#ifndef IL_NO_EXR
		case IL_EXR:
			return ilIsValidExrF(File);
		#endif

		#ifndef IL_NO_GIF
		case IL_GIF:
			return ilIsValidGifF(File);
		#endif

		#ifndef IL_NO_HDR
		case IL_HDR:
			return ilIsValidHdrF(File);
		#endif

		#ifndef IL_NO_ICNS
		case IL_ICNS:
			return ilIsValidIcnsF(File);
		#endif

		#ifndef IL_NO_IWI
		case IL_IWI:
			return ilIsValidIwiF(File);
		#endif

    	#ifndef IL_NO_ILBM
        case IL_ILBM:
            return ilIsValidIlbmF(File);
	    #endif

		#ifndef IL_NO_JP2
		case IL_JP2:
			return ilIsValidJp2F(File);
		#endif

		#ifndef IL_NO_LIF
		case IL_LIF:
			return ilIsValidLifF(File);
		#endif

		#ifndef IL_NO_MDL
		case IL_MDL:
			return ilIsValidMdlF(File);
		#endif

		#ifndef IL_NO_MP3
		case IL_MP3:
			return ilIsValidMp3F(File);
		#endif

		#ifndef IL_NO_PCX
		case IL_PCX:
			return ilIsValidPcxF(File);
		#endif

		#ifndef IL_NO_PIC
		case IL_PIC:
			return ilIsValidPicF(File);
		#endif

		#ifndef IL_NO_PNM
		case IL_PNM:
			return ilIsValidPnmF(File);
		#endif

		#ifndef IL_NO_PSD
		case IL_PSD:
			return ilIsValidPsdF(File);
		#endif

		#ifndef IL_NO_PSP
		case IL_PSP:
			return ilIsValidPspF(File);
		#endif

		#ifndef IL_NO_SGI
		case IL_SGI:
			return ilIsValidSgiF(File);
		#endif

		#ifndef IL_NO_SUN
		case IL_SUN:
			return ilIsValidSunF(File);
		#endif

		#ifndef IL_NO_TIF
		case IL_TIF:
			return ilIsValidTiffF(File);
		#endif

		#ifndef IL_NO_TPL
		case IL_TPL:
			return ilIsValidTplF(File);
		#endif

		#ifndef IL_NO_VTF
		case IL_VTF:
			return ilIsValidVtfF(File);
		#endif

		#ifndef IL_NO_XPM
		case IL_XPM:
			return ilIsValidXpmF(File);
		#endif
	}
