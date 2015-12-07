switch (tag) {
	case TIFFTAG_SUBFILETYPE:
		td->td_subfiletype = va_arg(ap, uint32);
		break;
	case TIFFTAG_IMAGEWIDTH:
		td->td_imagewidth = va_arg(ap, uint32);
		break;
	case TIFFTAG_IMAGELENGTH:
		td->td_imagelength = va_arg(ap, uint32);
		break;
	case TIFFTAG_BITSPERSAMPLE:
		td->td_bitspersample = (uint16) va_arg(ap, int);
		/*
		 * If the data require post-decoding processing
		 * to byte-swap samples, set it up here.  Note
		 * that since tags are required to be ordered,
		 * compression code can override this behaviour
		 * in the setup method if it wants to roll the
		 * post decoding work in with its normal work.
		 */
		if (tif->tif_flags & TIFF_SWAB) {
			if (td->td_bitspersample == 16)
				tif->tif_postdecode = _TIFFSwab16BitData;
			else if (td->td_bitspersample == 32)
				tif->tif_postdecode = _TIFFSwab32BitData;
			else if (td->td_bitspersample == 64)
				tif->tif_postdecode = _TIFFSwab64BitData;
		}
		break;
	case TIFFTAG_COMPRESSION:
		v = va_arg(ap, int) & 0xffff;
		/*
		 * If we're changing the compression scheme,
		 * the notify the previous module so that it
		 * can cleanup any state it's setup.
		 */
		if (TIFFFieldSet(tif, FIELD_COMPRESSION)) {
			if (td->td_compression == v)
				break;
			(*tif->tif_cleanup)(tif);
			tif->tif_flags &= ~TIFF_CODERSETUP;
		}
		/*
		 * Setup new compression routine state.
		 */
		if( (status = TIFFSetCompressionScheme(tif, v)) != 0 )
                    td->td_compression = v;
                else
                    status = 0;
		break;
	case TIFFTAG_PHOTOMETRIC:
		td->td_photometric = (uint16) va_arg(ap, int);
		break;
	case TIFFTAG_THRESHHOLDING:
		td->td_threshholding = (uint16) va_arg(ap, int);
		break;
	case TIFFTAG_FILLORDER:
		v = va_arg(ap, int);
		if (v != FILLORDER_LSB2MSB && v != FILLORDER_MSB2LSB)
			goto badvalue;
		td->td_fillorder = (uint16) v;
		break;
	case TIFFTAG_DOCUMENTNAME:
		_TIFFsetString(&td->td_documentname, va_arg(ap, char*));
		break;
	case TIFFTAG_ARTIST:
		_TIFFsetString(&td->td_artist, va_arg(ap, char*));
		break;
	case TIFFTAG_DATETIME:
		_TIFFsetString(&td->td_datetime, va_arg(ap, char*));
		break;
	case TIFFTAG_HOSTCOMPUTER:
		_TIFFsetString(&td->td_hostcomputer, va_arg(ap, char*));
		break;
	case TIFFTAG_IMAGEDESCRIPTION:
		_TIFFsetString(&td->td_imagedescription, va_arg(ap, char*));
		break;
	case TIFFTAG_MAKE:
		_TIFFsetString(&td->td_make, va_arg(ap, char*));
		break;
	case TIFFTAG_MODEL:
		_TIFFsetString(&td->td_model, va_arg(ap, char*));
		break;
	case TIFFTAG_SOFTWARE:
		_TIFFsetString(&td->td_software, va_arg(ap, char*));
		break;
	case TIFFTAG_COPYRIGHT:
		_TIFFsetString(&td->td_copyright, va_arg(ap, char*));
		break;
	case TIFFTAG_ORIENTATION:
		v = va_arg(ap, int);
		if (v < ORIENTATION_TOPLEFT || ORIENTATION_LEFTBOT < v) {
			TIFFWarning(tif->tif_name,
			    "Bad value %ld for \"%s\" tag ignored",
			    v, _TIFFFieldWithTag(tif, tag)->field_name);
		} else
			td->td_orientation = (uint16) v;
		break;
	case TIFFTAG_SAMPLESPERPIXEL:
		/* XXX should cross check -- e.g. if pallette, then 1 */
		v = va_arg(ap, int);
		if (v == 0)
			goto badvalue;
		td->td_samplesperpixel = (uint16) v;
		break;
	case TIFFTAG_ROWSPERSTRIP:
		v32 = va_arg(ap, uint32);
		if (v32 == 0)
			goto badvalue32;
		td->td_rowsperstrip = v32;
		if (!TIFFFieldSet(tif, FIELD_TILEDIMENSIONS)) {
			td->td_tilelength = v32;
			td->td_tilewidth = td->td_imagewidth;
		}
		break;
	case TIFFTAG_MINSAMPLEVALUE:
		td->td_minsamplevalue = (uint16) va_arg(ap, int);
		break;
	case TIFFTAG_MAXSAMPLEVALUE:
		td->td_maxsamplevalue = (uint16) va_arg(ap, int);
		break;
	case TIFFTAG_SMINSAMPLEVALUE:
		td->td_sminsamplevalue = (double) va_arg(ap, dblparam_t);
		break;
	case TIFFTAG_SMAXSAMPLEVALUE:
		td->td_smaxsamplevalue = (double) va_arg(ap, dblparam_t);
		break;
	case TIFFTAG_XRESOLUTION:
		td->td_xresolution = (float) va_arg(ap, dblparam_t);
		break;
	case TIFFTAG_YRESOLUTION:
		td->td_yresolution = (float) va_arg(ap, dblparam_t);
		break;
	case TIFFTAG_PLANARCONFIG:
		v = va_arg(ap, int);
		if (v != PLANARCONFIG_CONTIG && v != PLANARCONFIG_SEPARATE)
			goto badvalue;
		td->td_planarconfig = (uint16) v;
		break;
	case TIFFTAG_PAGENAME:
		_TIFFsetString(&td->td_pagename, va_arg(ap, char*));
		break;
	case TIFFTAG_XPOSITION:
		td->td_xposition = (float) va_arg(ap, dblparam_t);
		break;
	case TIFFTAG_YPOSITION:
		td->td_yposition = (float) va_arg(ap, dblparam_t);
		break;
	case TIFFTAG_RESOLUTIONUNIT:
		v = va_arg(ap, int);
		if (v < RESUNIT_NONE || RESUNIT_CENTIMETER < v)
			goto badvalue;
		td->td_resolutionunit = (uint16) v;
		break;
	case TIFFTAG_PAGENUMBER:
		td->td_pagenumber[0] = (uint16) va_arg(ap, int);
		td->td_pagenumber[1] = (uint16) va_arg(ap, int);
		break;
	case TIFFTAG_HALFTONEHINTS:
		td->td_halftonehints[0] = (uint16) va_arg(ap, int);
		td->td_halftonehints[1] = (uint16) va_arg(ap, int);
		break;
	case TIFFTAG_COLORMAP:
		v32 = (uint32)(1L<<td->td_bitspersample);
		_TIFFsetShortArray(&td->td_colormap[0], va_arg(ap, uint16*), v32);
		_TIFFsetShortArray(&td->td_colormap[1], va_arg(ap, uint16*), v32);
		_TIFFsetShortArray(&td->td_colormap[2], va_arg(ap, uint16*), v32);
		break;
	case TIFFTAG_EXTRASAMPLES:
		if (!setExtraSamples(td, ap, &v))
			goto badvalue;
		break;
	case TIFFTAG_MATTEING:
		td->td_extrasamples = (uint16) (va_arg(ap, int) != 0);
		if (td->td_extrasamples) {
			uint16 sv = EXTRASAMPLE_ASSOCALPHA;
			_TIFFsetShortArray(&td->td_sampleinfo, &sv, 1);
		}
		break;
	case TIFFTAG_TILEWIDTH:
		v32 = va_arg(ap, uint32);
		if (v32 % 16) {
			if (tif->tif_mode != O_RDONLY)
				goto badvalue32;
			TIFFWarning(tif->tif_name,
			    "Nonstandard tile width %d, convert file", v32);
		}
		td->td_tilewidth = v32;
		tif->tif_flags |= TIFF_ISTILED;
		break;
	case TIFFTAG_TILELENGTH:
		v32 = va_arg(ap, uint32);
		if (v32 % 16) {
			if (tif->tif_mode != O_RDONLY)
				goto badvalue32;
			TIFFWarning(tif->tif_name,
			    "Nonstandard tile length %d, convert file", v32);
		}
		td->td_tilelength = v32;
		tif->tif_flags |= TIFF_ISTILED;
		break;
	case TIFFTAG_TILEDEPTH:
		v32 = va_arg(ap, uint32);
		if (v32 == 0)
			goto badvalue32;
		td->td_tiledepth = v32;
		break;
	case TIFFTAG_DATATYPE:
		v = va_arg(ap, int);
		switch (v) {
		case DATATYPE_VOID:	v = SAMPLEFORMAT_VOID;	break;
		case DATATYPE_INT:	v = SAMPLEFORMAT_INT;	break;
		case DATATYPE_UINT:	v = SAMPLEFORMAT_UINT;	break;
		case DATATYPE_IEEEFP:	v = SAMPLEFORMAT_IEEEFP;break;
		default:		goto badvalue;
		}
		td->td_sampleformat = (uint16) v;
		break;
	case TIFFTAG_SAMPLEFORMAT:
		v = va_arg(ap, int);
		if (v < SAMPLEFORMAT_UINT || SAMPLEFORMAT_COMPLEXIEEEFP < v)
			goto badvalue;
		td->td_sampleformat = (uint16) v;
		break;
	case TIFFTAG_IMAGEDEPTH:
		td->td_imagedepth = va_arg(ap, uint32);
		break;
	case TIFFTAG_STONITS:
		d = va_arg(ap, dblparam_t);
		if (d <= 0.)
			goto badvaluedbl;
		td->td_stonits = d;
		break;

	/* Begin Pixar Tags */
 	case TIFFTAG_PIXAR_IMAGEFULLWIDTH:
 		td->td_imagefullwidth = va_arg(ap, uint32);
 		break;
 	case TIFFTAG_PIXAR_IMAGEFULLLENGTH:
 		td->td_imagefulllength = va_arg(ap, uint32);
 		break;
 	case TIFFTAG_PIXAR_TEXTUREFORMAT:
 		_TIFFsetString(&td->td_textureformat, va_arg(ap, char*));
 		break;
 	case TIFFTAG_PIXAR_WRAPMODES:
 		_TIFFsetString(&td->td_wrapmodes, va_arg(ap, char*));
 		break;
 	case TIFFTAG_PIXAR_FOVCOT:
 		td->td_fovcot = (float) va_arg(ap, dblparam_t);
 		break;
 	case TIFFTAG_PIXAR_MATRIX_WORLDTOSCREEN:
 		_TIFFsetFloatArray(&td->td_matrixWorldToScreen,
 			va_arg(ap, float*), 16);
 		break;
 	case TIFFTAG_PIXAR_MATRIX_WORLDTOCAMERA:
 		_TIFFsetFloatArray(&td->td_matrixWorldToCamera,
 			va_arg(ap, float*), 16);
 		break;
 	/* End Pixar Tags */	       

#if SUBIFD_SUPPORT
	case TIFFTAG_SUBIFD:
		if ((tif->tif_flags & TIFF_INSUBIFD) == 0) {
			td->td_nsubifd = (uint16) va_arg(ap, int);
			_TIFFsetLongArray(&td->td_subifd, va_arg(ap, uint32*),
			    (long) td->td_nsubifd);
		} else {
			TIFFError(tif->tif_name, "Sorry, cannot nest SubIFDs");
			status = 0;
		}
		break;
#endif
#ifdef YCBCR_SUPPORT
	case TIFFTAG_YCBCRCOEFFICIENTS:
		_TIFFsetFloatArray(&td->td_ycbcrcoeffs, va_arg(ap, float*), 3);
		break;
	case TIFFTAG_YCBCRPOSITIONING:
		td->td_ycbcrpositioning = (uint16) va_arg(ap, int);
		break;
	case TIFFTAG_YCBCRSUBSAMPLING:
		td->td_ycbcrsubsampling[0] = (uint16) va_arg(ap, int);
		td->td_ycbcrsubsampling[1] = (uint16) va_arg(ap, int);
		break;
#endif
#ifdef COLORIMETRY_SUPPORT
	case TIFFTAG_WHITEPOINT:
		_TIFFsetFloatArray(&td->td_whitepoint, va_arg(ap, float*), 2);
		break;
	case TIFFTAG_PRIMARYCHROMATICITIES:
		_TIFFsetFloatArray(&td->td_primarychromas, va_arg(ap, float*), 6);
		break;
	case TIFFTAG_TRANSFERFUNCTION:
		v = (td->td_samplesperpixel - td->td_extrasamples) > 1 ? 3 : 1;
		for (i = 0; i < v; i++)
			_TIFFsetShortArray(&td->td_transferfunction[i],
			    va_arg(ap, uint16*), 1L<<td->td_bitspersample);
		break;
	case TIFFTAG_REFERENCEBLACKWHITE:
		/* XXX should check for null range */
		_TIFFsetFloatArray(&td->td_refblackwhite, va_arg(ap, float*), 6);
		break;
#endif
#ifdef CMYK_SUPPORT
	case TIFFTAG_INKSET:
		td->td_inkset = (uint16) va_arg(ap, int);
		break;
	case TIFFTAG_DOTRANGE:
		/* XXX should check for null range */
		td->td_dotrange[0] = (uint16) va_arg(ap, int);
		td->td_dotrange[1] = (uint16) va_arg(ap, int);
		break;
	case TIFFTAG_INKNAMES:
		i = va_arg(ap, int);
		s = va_arg(ap, char*);
		i = checkInkNamesString(tif, i, s);
                status = i > 0;
		if( i > 0 ) {
			_TIFFsetNString(&td->td_inknames, s, i);
			td->td_inknameslen = i;
		}
		break;
	case TIFFTAG_NUMBEROFINKS:
		td->td_ninks = (uint16) va_arg(ap, int);
		break;
	case TIFFTAG_TARGETPRINTER:
		_TIFFsetString(&td->td_targetprinter, va_arg(ap, char*));
		break;
#endif
#ifdef ICC_SUPPORT
	case TIFFTAG_ICCPROFILE:
		td->td_profileLength = (uint32) va_arg(ap, uint32);
		_TIFFsetByteArray(&td->td_profileData, va_arg(ap, void*),
		    td->td_profileLength);
		break;
#endif
#ifdef PHOTOSHOP_SUPPORT
 	case TIFFTAG_PHOTOSHOP:
  		td->td_photoshopLength = (uint32) va_arg(ap, uint32);
  		_TIFFsetByteArray (&td->td_photoshopData, va_arg(ap, void*),
 			td->td_photoshopLength);
 		break;
#endif
#ifdef IPTC_SUPPORT
    case TIFFTAG_RICHTIFFIPTC: 
  		td->td_richtiffiptcLength = (uint32) va_arg(ap, uint32);
#ifdef PHOTOSHOP_SUPPORT
  		_TIFFsetLongArray ((uint32**)&td->td_richtiffiptcData, va_arg(ap, uint32*),
 			td->td_richtiffiptcLength);
#else
  		_TIFFsetByteArray (&td->td_photoshopData, va_arg(ap, void*),
 			td->td_photoshopLength);
#endif
 		break;
#endif
	default:
		/*
		 * This can happen if multiple images are open with
		 * different codecs which have private tags.  The
		 * global tag information table may then have tags
		 * that are valid for one file but not the other. 
		 * If the client tries to set a tag that is not valid
		 * for the image's codec then we'll arrive here.  This
		 * happens, for example, when tiffcp is used to convert
		 * between compression schemes and codec-specific tags
		 * are blindly copied.
		 */
		TIFFError("TIFFSetField",
		    "%s: Invalid %stag \"%s\" (not supported by codec)",
		    tif->tif_name, isPseudoTag(tag) ? "pseduo-" : "",
		    _TIFFFieldWithTag(tif, tag)->field_name);
		status = 0;
		break;
	}
