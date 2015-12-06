switch (Type)
	{
		case IL_TYPE_UNKNOWN:
			return ilSaveImage(FileName);

		#ifndef IL_NO_BMP
		case IL_BMP:
			return ilSaveBmp(FileName);
		#endif

		#ifndef IL_NO_CHEAD
		case IL_CHEAD:
			return ilSaveCHeader(FileName, "IL_IMAGE");
		#endif

		#ifndef IL_NO_DDS
		case IL_DDS:
    		return ilSaveDds(FileName);
		#endif

		#ifndef IL_NO_EXR
		case IL_EXR:
    		return ilSaveExr(FileName);
		#endif

		#ifndef IL_NO_HDR
		case IL_HDR:
			return ilSaveHdr(FileName);
		#endif

		#ifndef IL_NO_JP2
		case IL_JP2:
			return ilSaveJp2(FileName);
		#endif

		#ifndef IL_NO_JPG
		case IL_JPG:
			return ilSaveJpeg(FileName);
		#endif

		#ifndef IL_NO_PCX
		case IL_PCX:
			return ilSavePcx(FileName);
		#endif

		#ifndef IL_NO_PNG
		case IL_PNG:
			return ilSavePng(FileName);
		#endif

		#ifndef IL_NO_PNM
		case IL_PNM:
			return ilSavePnm(FileName);
		#endif

		#ifndef IL_NO_PSD
		case IL_PSD:
			return ilSavePsd(FileName);
		#endif

		#ifndef IL_NO_RAW
		case IL_RAW:
			return ilSaveRaw(FileName);
		#endif

		#ifndef IL_NO_SGI
		case IL_SGI:
			return ilSaveSgi(FileName);
		#endif

		#ifndef IL_NO_TGA
		case IL_TGA:
			return ilSaveTarga(FileName);
		#endif

		#ifndef IL_NO_TIF
		case IL_TIF:
			return ilSaveTiff(FileName);
		#endif

		#ifndef IL_NO_VTF
		case IL_VTF:
			return ilSaveVtf(FileName);
		#endif

		#ifndef IL_NO_WBMP
		case IL_WBMP:
			return ilSaveWbmp(FileName);
		#endif

		case IL_JASC_PAL:
			return ilSaveJascPal(FileName);
	}
