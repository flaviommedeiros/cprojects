switch (Type)
	{
		#ifndef IL_NO_BMP
		case IL_BMP:
			Ret = ilSaveBmpF(File);
			break;
		#endif

		#ifndef IL_NO_DDS
		case IL_DDS:
			Ret = ilSaveDdsF(File);
			break;
		#endif

		#ifndef IL_NO_EXR
		case IL_EXR:
			Ret = ilSaveExrF(File);
			break;
		#endif

		#ifndef IL_NO_HDR
		case IL_HDR:
			Ret = ilSaveHdrF(File);
			break;
		#endif

		#ifndef IL_NO_JP2
		case IL_JP2:
			Ret = ilSaveJp2F(File);
			break;
		#endif

		#ifndef IL_NO_JPG
			#ifndef IL_USE_IJL
			case IL_JPG:
				Ret = ilSaveJpegF(File);
				break;
			#endif
		#endif

		#ifndef IL_NO_PNM
		case IL_PNM:
			Ret = ilSavePnmF(File);
			break;
		#endif

		#ifndef IL_NO_PNG
		case IL_PNG:
			Ret = ilSavePngF(File);
			break;	
		#endif

		#ifndef IL_NO_PSD
		case IL_PSD:
			Ret = ilSavePsdF(File);
			break;
		#endif

		#ifndef IL_NO_RAW
		case IL_RAW:
			Ret = ilSaveRawF(File);
			break;
		#endif

		#ifndef IL_NO_SGI
		case IL_SGI:
			Ret = ilSaveSgiF(File);
			break;
		#endif

		#ifndef IL_NO_TGA
		case IL_TGA:
			Ret = ilSaveTargaF(File);
			break;
		#endif

		#ifndef IL_NO_VTF
		case IL_VTF:
			Ret = ilSaveVtfF(File);
			break;
		#endif

		#ifndef IL_NO_WBMP
		case IL_WBMP:
			Ret = ilSaveWbmpF(File);
			break;
		#endif

		#ifndef IL_NO_TIF
		case IL_TIF:
			Ret = ilSaveTiffF(File);
			break;
		#endif

		default:
			ilSetError(IL_INVALID_ENUM);
			return 0;
	}
