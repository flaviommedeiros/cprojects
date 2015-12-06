switch (Type)
	{
		case IL_TYPE_UNKNOWN:
			return IL_FALSE;

		#ifndef IL_NO_TGA
		case IL_TGA:
			return ilLoadTargaL(Lump, Size);
		#endif

		#ifndef IL_NO_JPG
		case IL_JPG:
			return ilLoadJpegL(Lump, Size);
		#endif

		#ifndef IL_NO_JP2
		case IL_JP2:
			return ilLoadJp2L(Lump, Size);
		#endif

		#ifndef IL_NO_DDS
		case IL_DDS:
			return ilLoadDdsL(Lump, Size);
		#endif

		#ifndef IL_NO_PNG
		case IL_PNG:
			return ilLoadPngL(Lump, Size);
		#endif

		#ifndef IL_NO_BLP
		case IL_BLP:
			return ilLoadBlpL(Lump, Size);
		#endif

		#ifndef IL_NO_BMP
		case IL_BMP:
			return ilLoadBmpL(Lump, Size);
		#endif

		#ifndef IL_NO_CUT
		case IL_CUT:
			return ilLoadCutL(Lump, Size);
		#endif

		#ifndef IL_NO_DICOM
		case IL_DICOM:
			return ilLoadDicomL(Lump, Size);
		#endif

		#ifndef IL_NO_DOOM
		case IL_DOOM:
			return ilLoadDoomL(Lump, Size);
		case IL_DOOM_FLAT:
			return ilLoadDoomFlatL(Lump, Size);
		#endif

		#ifndef IL_NO_DPX
		case IL_DPX:
			return ilLoadDpxL(Lump, Size);
		#endif

		#ifndef IL_NO_EXR
		case IL_EXR:
			return ilLoadExrL(Lump, Size);
		#endif

		#ifndef IL_NO_FITS
		case IL_FITS:
			return ilLoadFitsL(Lump, Size);
		#endif

		#ifndef IL_NO_FTX
		case IL_FTX:
			return ilLoadFtxL(Lump, Size);
		#endif

		#ifndef IL_NO_GIF
		case IL_GIF:
			return ilLoadGifL(Lump, Size);
		#endif

		#ifndef IL_NO_HDR
		case IL_HDR:
			return ilLoadHdrL(Lump, Size);
		#endif

		#ifndef IL_NO_ICO
		case IL_ICO:
			return ilLoadIconL(Lump, Size);
		#endif

		#ifndef IL_NO_ICNS
		case IL_ICNS:
			return ilLoadIcnsL(Lump, Size);
		#endif

		#ifndef IL_NO_IFF
		case IL_IFF:
			return ilLoadIffL(Lump, Size);
		#endif

		#ifndef IL_NO_ILBM
		case IL_ILBM:
			return ilLoadIlbmL(Lump, Size);
		#endif

		#ifndef IL_NO_IWI
		case IL_IWI:
			return ilLoadIwiL(Lump, Size);
		#endif

		#ifndef IL_NO_LIF
		case IL_LIF:
			return ilLoadLifL(Lump, Size);
		#endif

		#ifndef IL_NO_MDL
		case IL_MDL:
			return ilLoadMdlL(Lump, Size);
		#endif

		#ifndef IL_NO_MNG
		case IL_MNG:
			return ilLoadMngL(Lump, Size);
		#endif

		#ifndef IL_NO_MP3
		case IL_MP3:
			return ilLoadMp3L(Lump, Size);
		#endif

		#ifndef IL_NO_PCD
		case IL_PCD:
			return ilLoadPcdL(Lump, Size);
		#endif

		#ifndef IL_NO_PCX
		case IL_PCX:
			return ilLoadPcxL(Lump, Size);
		#endif

		#ifndef IL_NO_PIC
		case IL_PIC:
			return ilLoadPicL(Lump, Size);
		#endif

		#ifndef IL_NO_PIX
		case IL_PIX:
			return ilLoadPixL(Lump, Size);
		#endif

		#ifndef IL_NO_PNM
		case IL_PNM:
			return ilLoadPnmL(Lump, Size);
		#endif

		#ifndef IL_NO_PSD
		case IL_PSD:
			return ilLoadPsdL(Lump, Size);
		#endif

		#ifndef IL_NO_PSP
		case IL_PSP:
			return ilLoadPspL(Lump, Size);
		#endif

		#ifndef IL_NO_PXR
		case IL_PXR:
			return ilLoadPxrL(Lump, Size);
		#endif

		#ifndef IL_NO_RAW
		case IL_RAW:
			return ilLoadRawL(Lump, Size);
		#endif

		#ifndef IL_NO_ROT
		case IL_ROT:
			return ilLoadRotL(Lump, Size);
		#endif

		#ifndef IL_NO_SGI
		case IL_SGI:
			return ilLoadSgiL(Lump, Size);
		#endif

		#ifndef IL_NO_SUN
		case IL_SUN:
			return ilLoadSunL(Lump, Size);
		#endif

		#ifndef IL_NO_TEXTURE
		case IL_TEXTURE:
			return ilLoadTextureL(Lump, Size);
		#endif

		#ifndef IL_NO_TIF
		case IL_TIF:
			return ilLoadTiffL(Lump, Size);
		#endif

		#ifndef IL_NO_TPL
		case IL_TPL:
			return ilLoadTplL(Lump, Size);
		#endif

		#ifndef IL_NO_UTX
		case IL_UTX:
			return ilLoadUtxL(Lump, Size);
		#endif

		#ifndef IL_NO_VTF
		case IL_VTF:
			return ilLoadVtfL(Lump, Size);
		#endif

		#ifndef IL_NO_WAL
		case IL_WAL:
			return ilLoadWalL(Lump, Size);
		#endif

		#ifndef IL_NO_WBMP
		case IL_WBMP:
			return ilLoadWbmpL(Lump, Size);
		#endif

		#ifndef IL_NO_XPM
		case IL_XPM:
			return ilLoadXpmL(Lump, Size);
		#endif
	}
