switch (Type)
	{
		case IL_TYPE_UNKNOWN:
			bRet = ilLoadImage(FileName);
			break;

		#ifndef IL_NO_TGA
		case IL_TGA:
			bRet = ilLoadTarga(FileName);
			break;
		#endif

		#ifndef IL_NO_JPG
		case IL_JPG:
			bRet = ilLoadJpeg(FileName);
			break;
		#endif

		#ifndef IL_NO_JP2
		case IL_JP2:
			bRet = ilLoadJp2(FileName);
			break;
		#endif

		#ifndef IL_NO_DDS
		case IL_DDS:
			bRet = ilLoadDds(FileName);
			break;
		#endif

		#ifndef IL_NO_PNG
		case IL_PNG:
			bRet = ilLoadPng(FileName);
			break;
		#endif

		#ifndef IL_NO_BLP
		case IL_BLP:
			bRet = ilLoadBlp(FileName);
			break;
		#endif

		#ifndef IL_NO_BMP
		case IL_BMP:
			bRet = ilLoadBmp(FileName);
			break;
		#endif

		#ifndef IL_NO_DPX
		case IL_DPX:
			bRet = ilLoadDpx(FileName);
			break;
		#endif

		#ifndef IL_NO_GIF
		case IL_GIF:
			bRet = ilLoadGif(FileName);
			break;
		#endif

		#ifndef IL_NO_HDR
		case IL_HDR:
			bRet = ilLoadHdr(FileName);
			break;
		#endif

		#ifndef IL_NO_CUT
		case IL_CUT:
			bRet = ilLoadCut(FileName);
			break;
		#endif

		#ifndef IL_NO_DICOM
		case IL_DICOM:
			bRet = ilLoadDicom(FileName);
			break;
		#endif

		#ifndef IL_NO_DOOM
		case IL_DOOM:
			bRet = ilLoadDoom(FileName);
			break;
		case IL_DOOM_FLAT:
			bRet = ilLoadDoomFlat(FileName);
			break;
		#endif

		#ifndef IL_NO_EXR
		case IL_EXR:
			bRet = ilLoadExr(FileName);
			break;
		#endif

		#ifndef IL_NO_FITS
		case IL_FITS:
			bRet = ilLoadFits(FileName);
			break;
		#endif

		#ifndef IL_NO_FTX
		case IL_FTX:
			bRet = ilLoadFtx(FileName);
			break;
		#endif

		#ifndef IL_NO_ICO
		case IL_ICO:
			bRet = ilLoadIcon(FileName);
			break;
		#endif

		#ifndef IL_NO_ICNS
		case IL_ICNS:
			bRet = ilLoadIcns(FileName);
			break;
		#endif

		#ifndef IL_NO_IFF
		case IL_IFF:
			bRet = ilLoadIff(FileName);
			break;
		#endif

		#ifndef IL_NO_ILBM
		case IL_ILBM:
			bRet = ilLoadIlbm(FileName);
			break;
		#endif

		#ifndef IL_NO_IWI
		case IL_IWI:
			bRet = ilLoadIwi(FileName);
			break;
		#endif

		#ifndef IL_NO_LIF
		case IL_LIF:
			bRet = ilLoadLif(FileName);
			break;
		#endif

		#ifndef IL_NO_MDL
		case IL_MDL:
			bRet = ilLoadMdl(FileName);
			break;
		#endif

		#ifndef IL_NO_MNG
		case IL_MNG:
			bRet = ilLoadMng(FileName);
			break;
		#endif

		#ifndef IL_NO_MP3
		case IL_MP3:
			bRet = ilLoadMp3(FileName);
			break;
		#endif

		#ifndef IL_NO_PCD
		case IL_PCD:
			ilLoadPcd(FileName);
			break;
		#endif

		#ifndef IL_NO_PCX
		case IL_PCX:
			bRet = ilLoadPcx(FileName);
			break;
		#endif

		#ifndef IL_NO_PIC
		case IL_PIC:
			bRet = ilLoadPic(FileName);
			break;
		#endif

		#ifndef IL_NO_PIX
		case IL_PIX:
			bRet = ilLoadPix(FileName);
			break;
		#endif

		#ifndef IL_NO_PNM
		case IL_PNM:
			bRet = ilLoadPnm(FileName);
			break;
		#endif

		#ifndef IL_NO_PSD
		case IL_PSD:
			bRet = ilLoadPsd(FileName);
			break;
		#endif

		#ifndef IL_NO_PSP
		case IL_PSP:
			bRet = ilLoadPsp(FileName);
			break;
		#endif

		#ifndef IL_NO_PXR
		case IL_PXR:
			bRet = ilLoadPxr(FileName);
			break;
		#endif

		#ifndef IL_NO_RAW
		case IL_RAW:
			bRet = ilLoadRaw(FileName);
			break;
		#endif

		#ifndef IL_NO_ROT
		case IL_ROT:
			bRet = ilLoadRot(FileName);
			break;
		#endif

		#ifndef IL_NO_SGI
		case IL_SGI:
			bRet = ilLoadSgi(FileName);
			break;
		#endif

		#ifndef IL_NO_SUN
		case IL_SUN:
			bRet = ilLoadSun(FileName);
			break;
		#endif

		#ifndef IL_NO_TEXTURE
		case IL_TEXTURE:
			bRet = ilLoadTexture(FileName);
			break;
		#endif

		#ifndef IL_NO_TIF
		case IL_TIF:
			bRet = ilLoadTiff(FileName);
			break;
		#endif

		#ifndef IL_NO_TPL
		case IL_TPL:
			bRet = ilLoadTpl(FileName);
			break;
		#endif

		#ifndef IL_NO_UTX
		case IL_UTX:
			bRet = ilLoadUtx(FileName);
			break;
		#endif

		#ifndef IL_NO_VTF
		case IL_VTF:
			bRet = ilLoadVtf(FileName);
			break;
		#endif

		#ifndef IL_NO_WAL
		case IL_WAL:
			bRet = ilLoadWal(FileName);
			break;
		#endif

		#ifndef IL_NO_WBMP
		case IL_WBMP:
			bRet = ilLoadWbmp(FileName);
			break;
		#endif

		#ifndef IL_NO_XPM
		case IL_XPM:
			bRet = ilLoadXpm(FileName);
			break;
		#endif

		#ifndef IL_NO_WDP
		case IL_WDP:
			bRet = ilLoadWdp(FileName);
			break;
		#endif

		default:
			ilSetError(IL_INVALID_ENUM);
			bRet = IL_FALSE;
	}
