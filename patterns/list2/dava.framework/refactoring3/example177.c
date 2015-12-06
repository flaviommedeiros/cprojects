switch (Type)
	{
		#ifndef IL_NO_BMP
		case IL_BMP:
			ilSaveBmpL(NULL, 0);
			break;
		#endif//IL_NO_BMP

		#ifndef IL_NO_DDS
		case IL_DDS:
			ilSaveDdsL(NULL, 0);
			break;
		#endif//IL_NO_DDS

		#ifndef IL_NO_EXR
		case IL_EXR:
			ilSaveExrL(NULL, 0);
			break;
		#endif//IL_NO_EXR

		#ifndef IL_NO_HDR
		case IL_HDR:
			ilSaveHdrL(NULL, 0);
			break;
		#endif//IL_NO_HDR

		#ifndef IL_NO_JP2
		case IL_JP2:
			ilSaveJp2L(NULL, 0);
			break;
		#endif//IL_NO_JP2

		#ifndef IL_NO_JPG
		case IL_JPG:
			ilSaveJpegL(NULL, 0);
			break;
		#endif//IL_NO_JPG

		#ifndef IL_NO_PCX
		case IL_PCX:
			ilSavePcxL(NULL, 0);
			break;
		#endif//IL_NO_PCX

		#ifndef IL_NO_PNG
		case IL_PNG:
			ilSavePngL(NULL, 0);
			break;
		#endif//IL_NO_PNG

		#ifndef IL_NO_PNM
		case IL_PNM:
			ilSavePnmL(NULL, 0);
			break;
		#endif//IL_NO_PNM

		#ifndef IL_NO_PSD
		case IL_PSD:
			ilSavePsdL(NULL, 0);
			break;
		#endif//IL_NO_PSD

		#ifndef IL_NO_RAW
		case IL_RAW:
			ilSaveRawL(NULL, 0);
			break;
		#endif//IL_NO_RAW

		#ifndef IL_NO_SGI
		case IL_SGI:
			ilSaveSgiL(NULL, 0);
			break;
		#endif//IL_NO_SGI

		#ifndef IL_NO_TGA
		case IL_TGA:
			//ilSaveTargaL(NULL, 0);
			return iTargaSize();
			break;
		#endif//IL_NO_TGA

		#ifndef IL_NO_TIF
		case IL_TIF:
			ilSaveTiffL(NULL, 0);
			break;
		#endif//IL_NO_TIF

		#ifndef IL_NO_WBMP
		case IL_WBMP:
			ilSaveWbmpL(NULL, 0);
			break;
		#endif//IL_NO_WBMP

		default:
			// 0 is an error for this.
			ilSetError(IL_INVALID_ENUM);
			return 0;
	}
