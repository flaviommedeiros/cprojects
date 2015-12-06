switch (Type)
	{
		case IL_TYPE_UNKNOWN:
			return IL_FALSE;

		#ifndef IL_NO_TGA
		case IL_TGA:
			return ilLoadTargaF(File);
		#endif

		#ifndef IL_NO_JPG
			#ifndef IL_USE_IJL
			case IL_JPG:
				return ilLoadJpegF(File);
			#endif
		#endif

		#ifndef IL_NO_JP2
		case IL_JP2:
			return ilLoadJp2F(File);
		#endif

		#ifndef IL_NO_DDS
		case IL_DDS:
			return ilLoadDdsF(File);
		#endif

		#ifndef IL_NO_PNG
		case IL_PNG:
			return ilLoadPngF(File);
		#endif

		#ifndef IL_NO_BLP
		case IL_BLP:
			return ilLoadBlpF(File);
		#endif

		#ifndef IL_NO_BMP
		case IL_BMP:
			return ilLoadBmpF(File);
		#endif

		#ifndef IL_NO_CUT
		case IL_CUT:
			return ilLoadCutF(File);
		#endif

		#ifndef IL_NO_DICOM
		case IL_DICOM:
			return ilLoadDicomF(File);
		#endif

		#ifndef IL_NO_DOOM
		case IL_DOOM:
			return ilLoadDoomF(File);
		case IL_DOOM_FLAT:
			return ilLoadDoomFlatF(File);
		#endif

		#ifndef IL_NO_DPX
		case IL_DPX:
			return ilLoadDpxF(File);
		#endif

		#ifndef IL_NO_EXR
		case IL_EXR:
			return ilLoadExrF(File);
		#endif

		#ifndef IL_NO_FITS
		case IL_FITS:
			return ilLoadFitsF(File);
		#endif

		#ifndef IL_NO_FTX
		case IL_FTX:
			return ilLoadFtxF(File);
		#endif

		#ifndef IL_NO_GIF
		case IL_GIF:
			return ilLoadGifF(File);
		#endif

		#ifndef IL_NO_HDR
		case IL_HDR:
			return ilLoadHdrF(File);
		#endif

		#ifndef IL_NO_ICO
		case IL_ICO:
			return ilLoadIconF(File);
		#endif

		#ifndef IL_NO_ICNS
		case IL_ICNS:
			return ilLoadIcnsF(File);
		#endif

		#ifndef IL_NO_IFF
		case IL_IFF:
			return ilLoadIffF(File);
		#endif

		#ifndef IL_NO_ILBM
		case IL_ILBM:
			return ilLoadIlbmF(File);
		#endif

		#ifndef IL_NO_IWI
		case IL_IWI:
			return ilLoadIwiF(File);
		#endif

		#ifndef IL_NO_LIF
		case IL_LIF:
			return ilLoadLifF(File);
		#endif

		#ifndef IL_NO_MDL
		case IL_MDL:
			return ilLoadMdlF(File);
		#endif

		#ifndef IL_NO_MNG
		case IL_MNG:
			return ilLoadMngF(File);
		#endif

		#ifndef IL_NO_MP3
		case IL_MP3:
			return ilLoadMp3F(File);
		#endif

		#ifndef IL_NO_PCD
		case IL_PCD:
			return ilLoadPcdF(File);
		#endif

		#ifndef IL_NO_PCX
		case IL_PCX:
			return ilLoadPcxF(File);
		#endif

		#ifndef IL_NO_PIC
		case IL_PIC:
			return ilLoadPicF(File);
		#endif

		#ifndef IL_NO_PIX
		case IL_PIX:
			return ilLoadPixF(File);
		#endif

		#ifndef IL_NO_PNM
		case IL_PNM:
			return ilLoadPnmF(File);
		#endif

		#ifndef IL_NO_PSD
		case IL_PSD:
			return ilLoadPsdF(File);
		#endif

		#ifndef IL_NO_PSP
		case IL_PSP:
			return ilLoadPspF(File);
		#endif

		#ifndef IL_NO_PXR
		case IL_PXR:
			return ilLoadPxrF(File);
		#endif

		#ifndef IL_NO_RAW
		case IL_RAW:
			return ilLoadRawF(File);
		#endif

		#ifndef IL_NO_ROT
		case IL_ROT:
			return ilLoadRotF(File);
		#endif

		#ifndef IL_NO_SGI
		case IL_SGI:
			return ilLoadSgiF(File);
		#endif

		#ifndef IL_NO_SUN
		case IL_SUN:
			return ilLoadSunF(File);
		#endif

		#ifndef IL_NO_TEXTURE
		case IL_TEXTURE:
			return ilLoadTextureF(File);
		#endif

		#ifndef IL_NO_TIF
		case IL_TIF:
			return ilLoadTiffF(File);
		#endif

		#ifndef IL_NO_TPL
		case IL_TPL:
			return ilLoadTplF(File);
		#endif

		#ifndef IL_NO_UTX
		case IL_UTX:
			return ilLoadUtxF(File);
		#endif

		#ifndef IL_NO_VTF
		case IL_VTF:
			return ilLoadVtfF(File);
		#endif

		#ifndef IL_NO_WAL
		case IL_WAL:
			return ilLoadWalF(File);
		#endif

		#ifndef IL_NO_WBMP
		case IL_WBMP:
			return ilLoadWbmpF(File);
		#endif

		#ifndef IL_NO_XPM
		case IL_XPM:
			return ilLoadXpmF(File);
		#endif
	}
