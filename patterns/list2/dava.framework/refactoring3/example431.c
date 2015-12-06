switch (Type)
	{
		#ifndef IL_NO_BMP
		case IL_BMP:
			return ilSaveBmpL(Lump, Size);
		#endif

		#ifndef IL_NO_EXR
		case IL_EXR:
			return ilSaveExrL(Lump, Size);
		#endif

		#ifndef IL_NO_HDR
		case IL_HDR:
			return ilSaveHdrL(Lump, Size);
		#endif

		#ifndef IL_NO_JP2
		case IL_JP2:
			return ilSaveJp2L(Lump, Size);
		#endif

		#ifndef IL_NO_JPG
		case IL_JPG:
			return ilSaveJpegL(Lump, Size);
		#endif

		#ifndef IL_NO_PNG
		case IL_PNG:
			return ilSavePngL(Lump, Size);
		#endif

		#ifndef IL_NO_PNM
		case IL_PNM:
			return ilSavePnmL(Lump, Size);
		#endif

		#ifndef IL_NO_PSD
		case IL_PSD:
			return ilSavePsdL(Lump, Size);
		#endif

		#ifndef IL_NO_RAW
		case IL_RAW:
			return ilSaveRawL(Lump, Size);
		#endif

		#ifndef IL_NO_SGI
		case IL_SGI:
			return ilSaveSgiL(Lump, Size);
		#endif

		#ifndef IL_NO_TGA
		case IL_TGA:
			return ilSaveTargaL(Lump, Size);
		#endif

		#ifndef IL_NO_DDS
		case IL_DDS:
			return ilSaveDdsL(Lump, Size);
		#endif

		#ifndef IL_NO_VTF
		case IL_VTF:
			return ilSaveVtfL(Lump, Size);
		#endif

		#ifndef IL_NO_WBMP
		case IL_WBMP:
			return ilSaveWbmpL(Lump, Size);
		#endif

		#ifndef IL_NO_TIF
		case IL_TIF:
			return ilSaveTiffL(Lump, Size);
		#endif
	}
