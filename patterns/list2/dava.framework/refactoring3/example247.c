switch (Type)
	{
		#ifndef IL_NO_TGA
		case IL_TGA:
			return ilIsValidTgaL(Lump, Size);
		#endif

		#ifndef IL_NO_JPG
		case IL_JPG:
			return ilIsValidJpegL(Lump, Size);
		#endif

		#ifndef IL_NO_DDS
		case IL_DDS:
			return ilIsValidDdsL(Lump, Size);
		#endif

		#ifndef IL_NO_PNG
		case IL_PNG:
			return ilIsValidPngL(Lump, Size);
		#endif

		#ifndef IL_NO_BMP
		case IL_BMP:
			return ilIsValidBmpL(Lump, Size);
		#endif

		#ifndef IL_NO_DICOM
		case IL_DICOM:
			return ilIsValidDicomL(Lump, Size);
		#endif

		#ifndef IL_NO_EXR
		case IL_EXR:
			return ilIsValidExrL(Lump, Size);
		#endif

		#ifndef IL_NO_GIF
		case IL_GIF:
			return ilIsValidGifL(Lump, Size);
		#endif

		#ifndef IL_NO_HDR
		case IL_HDR:
			return ilIsValidHdrL(Lump, Size);
		#endif

		#ifndef IL_NO_ICNS
		case IL_ICNS:
			return ilIsValidIcnsL(Lump, Size);
		#endif

		#ifndef IL_NO_IWI
		case IL_IWI:
			return ilIsValidIwiL(Lump, Size);
		#endif

    	#ifndef IL_NO_ILBM
        case IL_ILBM:
            return ilIsValidIlbmL(Lump, Size);
	    #endif

		#ifndef IL_NO_JP2
		case IL_JP2:
			return ilIsValidJp2L(Lump, Size);
		#endif

		#ifndef IL_NO_LIF
		case IL_LIF:
			return ilIsValidLifL(Lump, Size);
		#endif

		#ifndef IL_NO_MDL
		case IL_MDL:
			return ilIsValidMdlL(Lump, Size);
		#endif

		#ifndef IL_NO_MP3
		case IL_MP3:
			return ilIsValidMp3L(Lump, Size);
		#endif

		#ifndef IL_NO_PCX
		case IL_PCX:
			return ilIsValidPcxL(Lump, Size);
		#endif

		#ifndef IL_NO_PIC
		case IL_PIC:
			return ilIsValidPicL(Lump, Size);
		#endif

		#ifndef IL_NO_PNM
		case IL_PNM:
			return ilIsValidPnmL(Lump, Size);
		#endif

		#ifndef IL_NO_PSD
		case IL_PSD:
			return ilIsValidPsdL(Lump, Size);
		#endif

		#ifndef IL_NO_PSP
		case IL_PSP:
			return ilIsValidPspL(Lump, Size);
		#endif

		#ifndef IL_NO_SGI
		case IL_SGI:
			return ilIsValidSgiL(Lump, Size);
		#endif

		#ifndef IL_NO_SUN
		case IL_SUN:
			return ilIsValidSunL(Lump, Size);
		#endif

		#ifndef IL_NO_TIF
		case IL_TIF:
			return ilIsValidTiffL(Lump, Size);
		#endif

		#ifndef IL_NO_TPL
		case IL_TPL:
			return ilIsValidTplL(Lump, Size);
		#endif

		#ifndef IL_NO_VTF
		case IL_VTF:
			return ilIsValidVtfL(Lump, Size);
		#endif

		#ifndef IL_NO_XPM
		case IL_XPM:
			return ilIsValidXpmL(Lump, Size);
		#endif
	}
