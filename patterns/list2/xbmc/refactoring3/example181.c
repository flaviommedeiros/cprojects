switch (tag) {
	case TIFFTAG_SUBFILETYPE:
		*va_arg(ap, uint32*) = td->td_subfiletype;
		break;
	case TIFFTAG_IMAGEWIDTH:
		*va_arg(ap, uint32*) = td->td_imagewidth;
		break;
	case TIFFTAG_IMAGELENGTH:
		*va_arg(ap, uint32*) = td->td_imagelength;
		break;
	case TIFFTAG_BITSPERSAMPLE:
		*va_arg(ap, uint16*) = td->td_bitspersample;
		break;
	case TIFFTAG_COMPRESSION:
		*va_arg(ap, uint16*) = td->td_compression;
		break;
	case TIFFTAG_PHOTOMETRIC:
		*va_arg(ap, uint16*) = td->td_photometric;
		break;
	case TIFFTAG_THRESHHOLDING:
		*va_arg(ap, uint16*) = td->td_threshholding;
		break;
	case TIFFTAG_FILLORDER:
		*va_arg(ap, uint16*) = td->td_fillorder;
		break;
	case TIFFTAG_DOCUMENTNAME:
		*va_arg(ap, char**) = td->td_documentname;
		break;
	case TIFFTAG_ARTIST:
		*va_arg(ap, char**) = td->td_artist;
		break;
	case TIFFTAG_DATETIME:
		*va_arg(ap, char**) = td->td_datetime;
		break;
	case TIFFTAG_HOSTCOMPUTER:
		*va_arg(ap, char**) = td->td_hostcomputer;
		break;
	case TIFFTAG_IMAGEDESCRIPTION:
		*va_arg(ap, char**) = td->td_imagedescription;
		break;
	case TIFFTAG_MAKE:
		*va_arg(ap, char**) = td->td_make;
		break;
	case TIFFTAG_MODEL:
		*va_arg(ap, char**) = td->td_model;
		break;
	case TIFFTAG_SOFTWARE:
		*va_arg(ap, char**) = td->td_software;
		break;
	case TIFFTAG_COPYRIGHT:
		*va_arg(ap, char**) = td->td_copyright;
		break;
	case TIFFTAG_ORIENTATION:
		*va_arg(ap, uint16*) = td->td_orientation;
		break;
	case TIFFTAG_SAMPLESPERPIXEL:
		*va_arg(ap, uint16*) = td->td_samplesperpixel;
		break;
	case TIFFTAG_ROWSPERSTRIP:
		*va_arg(ap, uint32*) = td->td_rowsperstrip;
		break;
	case TIFFTAG_MINSAMPLEVALUE:
		*va_arg(ap, uint16*) = td->td_minsamplevalue;
		break;
	case TIFFTAG_MAXSAMPLEVALUE:
		*va_arg(ap, uint16*) = td->td_maxsamplevalue;
		break;
	case TIFFTAG_SMINSAMPLEVALUE:
		*va_arg(ap, double*) = td->td_sminsamplevalue;
		break;
	case TIFFTAG_SMAXSAMPLEVALUE:
		*va_arg(ap, double*) = td->td_smaxsamplevalue;
		break;
	case TIFFTAG_XRESOLUTION:
		*va_arg(ap, float*) = td->td_xresolution;
		break;
	case TIFFTAG_YRESOLUTION:
		*va_arg(ap, float*) = td->td_yresolution;
		break;
	case TIFFTAG_PLANARCONFIG:
		*va_arg(ap, uint16*) = td->td_planarconfig;
		break;
	case TIFFTAG_XPOSITION:
		*va_arg(ap, float*) = td->td_xposition;
		break;
	case TIFFTAG_YPOSITION:
		*va_arg(ap, float*) = td->td_yposition;
		break;
	case TIFFTAG_PAGENAME:
		*va_arg(ap, char**) = td->td_pagename;
		break;
	case TIFFTAG_RESOLUTIONUNIT:
		*va_arg(ap, uint16*) = td->td_resolutionunit;
		break;
	case TIFFTAG_PAGENUMBER:
		*va_arg(ap, uint16*) = td->td_pagenumber[0];
		*va_arg(ap, uint16*) = td->td_pagenumber[1];
		break;
	case TIFFTAG_HALFTONEHINTS:
		*va_arg(ap, uint16*) = td->td_halftonehints[0];
		*va_arg(ap, uint16*) = td->td_halftonehints[1];
		break;
	case TIFFTAG_COLORMAP:
		*va_arg(ap, uint16**) = td->td_colormap[0];
		*va_arg(ap, uint16**) = td->td_colormap[1];
		*va_arg(ap, uint16**) = td->td_colormap[2];
		break;
	case TIFFTAG_STRIPOFFSETS:
	case TIFFTAG_TILEOFFSETS:
		*va_arg(ap, uint32**) = td->td_stripoffset;
		break;
	case TIFFTAG_STRIPBYTECOUNTS:
	case TIFFTAG_TILEBYTECOUNTS:
		*va_arg(ap, uint32**) = td->td_stripbytecount;
		break;
	case TIFFTAG_MATTEING:
		*va_arg(ap, uint16*) =
		    (td->td_extrasamples == 1 &&
		     td->td_sampleinfo[0] == EXTRASAMPLE_ASSOCALPHA);
		break;
	case TIFFTAG_EXTRASAMPLES:
		*va_arg(ap, uint16*) = td->td_extrasamples;
		*va_arg(ap, uint16**) = td->td_sampleinfo;
		break;
	case TIFFTAG_TILEWIDTH:
		*va_arg(ap, uint32*) = td->td_tilewidth;
		break;
	case TIFFTAG_TILELENGTH:
		*va_arg(ap, uint32*) = td->td_tilelength;
		break;
	case TIFFTAG_TILEDEPTH:
		*va_arg(ap, uint32*) = td->td_tiledepth;
		break;
	case TIFFTAG_DATATYPE:
		switch (td->td_sampleformat) {
		case SAMPLEFORMAT_UINT:
			*va_arg(ap, uint16*) = DATATYPE_UINT;
			break;
		case SAMPLEFORMAT_INT:
			*va_arg(ap, uint16*) = DATATYPE_INT;
			break;
		case SAMPLEFORMAT_IEEEFP:
			*va_arg(ap, uint16*) = DATATYPE_IEEEFP;
			break;
		case SAMPLEFORMAT_VOID:
			*va_arg(ap, uint16*) = DATATYPE_VOID;
			break;
		}
		break;
	case TIFFTAG_SAMPLEFORMAT:
		*va_arg(ap, uint16*) = td->td_sampleformat;
		break;
	case TIFFTAG_IMAGEDEPTH:
		*va_arg(ap, uint32*) = td->td_imagedepth;
		break;
	case TIFFTAG_STONITS:
		*va_arg(ap, double*) = td->td_stonits;
		break;
#if SUBIFD_SUPPORT
	case TIFFTAG_SUBIFD:
		*va_arg(ap, uint16*) = td->td_nsubifd;
		*va_arg(ap, uint32**) = td->td_subifd;
		break;
#endif
#ifdef YCBCR_SUPPORT
	case TIFFTAG_YCBCRCOEFFICIENTS:
		*va_arg(ap, float**) = td->td_ycbcrcoeffs;
		break;
	case TIFFTAG_YCBCRPOSITIONING:
		*va_arg(ap, uint16*) = td->td_ycbcrpositioning;
		break;
	case TIFFTAG_YCBCRSUBSAMPLING:
		*va_arg(ap, uint16*) = td->td_ycbcrsubsampling[0];
		*va_arg(ap, uint16*) = td->td_ycbcrsubsampling[1];
		break;
#endif
#ifdef COLORIMETRY_SUPPORT
	case TIFFTAG_WHITEPOINT:
		*va_arg(ap, float**) = td->td_whitepoint;
		break;
	case TIFFTAG_PRIMARYCHROMATICITIES:
		*va_arg(ap, float**) = td->td_primarychromas;
		break;
	case TIFFTAG_TRANSFERFUNCTION:
		*va_arg(ap, uint16**) = td->td_transferfunction[0];
		if (td->td_samplesperpixel - td->td_extrasamples > 1) {
			*va_arg(ap, uint16**) = td->td_transferfunction[1];
			*va_arg(ap, uint16**) = td->td_transferfunction[2];
		}
		break;
	case TIFFTAG_REFERENCEBLACKWHITE:
		*va_arg(ap, float**) = td->td_refblackwhite;
		break;
#endif
#ifdef CMYK_SUPPORT
	case TIFFTAG_INKSET:
		*va_arg(ap, uint16*) = td->td_inkset;
		break;
	case TIFFTAG_DOTRANGE:
		*va_arg(ap, uint16*) = td->td_dotrange[0];
		*va_arg(ap, uint16*) = td->td_dotrange[1];
		break;
	case TIFFTAG_INKNAMES:
		*va_arg(ap, char**) = td->td_inknames;
		break;
	case TIFFTAG_NUMBEROFINKS:
		*va_arg(ap, uint16*) = td->td_ninks;
		break;
	case TIFFTAG_TARGETPRINTER:
		*va_arg(ap, char**) = td->td_targetprinter;
		break;
#endif
#ifdef ICC_SUPPORT
	case TIFFTAG_ICCPROFILE:
		*va_arg(ap, uint32*) = td->td_profileLength;
		*va_arg(ap, void**) = td->td_profileData;
		break;
#endif
#ifdef PHOTOSHOP_SUPPORT
 	case TIFFTAG_PHOTOSHOP:
 		*va_arg(ap, uint32*) = td->td_photoshopLength;
 		*va_arg(ap, void**) = td->td_photoshopData;
 		break;
#endif
#ifdef IPTC_SUPPORT
 	case TIFFTAG_RICHTIFFIPTC:
 		*va_arg(ap, uint32*) = td->td_richtiffiptcLength;
 		*va_arg(ap, void**) = td->td_richtiffiptcData;
 		break;
#endif
 	/* Begin Pixar Tags */
 	case TIFFTAG_PIXAR_IMAGEFULLWIDTH:
 		*va_arg(ap, uint32*) = td->td_imagefullwidth;
 		break;
 	case TIFFTAG_PIXAR_IMAGEFULLLENGTH:
 		*va_arg(ap, uint32*) = td->td_imagefulllength;
 		break;
 	case TIFFTAG_PIXAR_TEXTUREFORMAT:
 		*va_arg(ap, char**) = td->td_textureformat;
 		break;
 	case TIFFTAG_PIXAR_WRAPMODES:
 		*va_arg(ap, char**) = td->td_wrapmodes;
 		break;
 	case TIFFTAG_PIXAR_FOVCOT:
 		*va_arg(ap, float*) = td->td_fovcot;
 		break;
 	case TIFFTAG_PIXAR_MATRIX_WORLDTOSCREEN:
 		*va_arg(ap, float**) = td->td_matrixWorldToScreen;
 		break;
 	case TIFFTAG_PIXAR_MATRIX_WORLDTOCAMERA:
 		*va_arg(ap, float**) = td->td_matrixWorldToCamera;
 		break;
 	/* End Pixar Tags */

	default:
		/*
		 * This can happen if multiple images are open with
		 * different codecs which have private tags.  The
		 * global tag information table may then have tags
		 * that are valid for one file but not the other. 
		 * If the client tries to get a tag that is not valid
		 * for the image's codec then we'll arrive here.
		 */
		TIFFError("TIFFGetField",
		    "%s: Invalid %stag \"%s\" (not supported by codec)",
		    tif->tif_name, isPseudoTag(tag) ? "pseudo-" : "",
		    _TIFFFieldWithTag(tif, tag)->field_name);
		break;
	}
