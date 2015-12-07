switch (tag) {
	case TIFFTAG_SUBFILETYPE:
		*va_arg(ap, uint32 *) = td->td_subfiletype;
		return (1);
	case TIFFTAG_BITSPERSAMPLE:
		*va_arg(ap, uint16 *) = td->td_bitspersample;
		return (1);
	case TIFFTAG_THRESHHOLDING:
		*va_arg(ap, uint16 *) = td->td_threshholding;
		return (1);
	case TIFFTAG_FILLORDER:
		*va_arg(ap, uint16 *) = td->td_fillorder;
		return (1);
	case TIFFTAG_ORIENTATION:
		*va_arg(ap, uint16 *) = td->td_orientation;
		return (1);
	case TIFFTAG_SAMPLESPERPIXEL:
		*va_arg(ap, uint16 *) = td->td_samplesperpixel;
		return (1);
	case TIFFTAG_ROWSPERSTRIP:
		*va_arg(ap, uint32 *) = td->td_rowsperstrip;
		return (1);
	case TIFFTAG_MINSAMPLEVALUE:
		*va_arg(ap, uint16 *) = td->td_minsamplevalue;
		return (1);
	case TIFFTAG_MAXSAMPLEVALUE:
		*va_arg(ap, uint16 *) = td->td_maxsamplevalue;
		return (1);
	case TIFFTAG_PLANARCONFIG:
		*va_arg(ap, uint16 *) = td->td_planarconfig;
		return (1);
	case TIFFTAG_RESOLUTIONUNIT:
		*va_arg(ap, uint16 *) = td->td_resolutionunit;
		return (1);
#ifdef CMYK_SUPPORT
	case TIFFTAG_DOTRANGE:
		*va_arg(ap, uint16 *) = 0;
		*va_arg(ap, uint16 *) = (1<<td->td_bitspersample)-1;
		return (1);
	case TIFFTAG_INKSET:
		*va_arg(ap, uint16 *) = td->td_inkset;
		return (1);
	case TIFFTAG_NUMBEROFINKS:
		*va_arg(ap, uint16 *) = td->td_ninks;
		return (1);
#endif
	case TIFFTAG_EXTRASAMPLES:
		*va_arg(ap, uint16 *) = td->td_extrasamples;
		*va_arg(ap, uint16 **) = td->td_sampleinfo;
		return (1);
	case TIFFTAG_MATTEING:
		*va_arg(ap, uint16 *) =
		    (td->td_extrasamples == 1 &&
		     td->td_sampleinfo[0] == EXTRASAMPLE_ASSOCALPHA);
		return (1);
	case TIFFTAG_TILEDEPTH:
		*va_arg(ap, uint32 *) = td->td_tiledepth;
		return (1);
	case TIFFTAG_DATATYPE:
		*va_arg(ap, uint16 *) = td->td_sampleformat-1;
		return (1);
	case TIFFTAG_SAMPLEFORMAT:
		*va_arg(ap, uint16 *) = td->td_sampleformat;
                return(1);
	case TIFFTAG_IMAGEDEPTH:
		*va_arg(ap, uint32 *) = td->td_imagedepth;
		return (1);
#ifdef YCBCR_SUPPORT
	case TIFFTAG_YCBCRCOEFFICIENTS:
		if (!td->td_ycbcrcoeffs) {
			td->td_ycbcrcoeffs = (float *)
			    _TIFFmalloc(3*sizeof (float));
			/* defaults are from CCIR Recommendation 601-1 */
			td->td_ycbcrcoeffs[0] = 0.299f;
			td->td_ycbcrcoeffs[1] = 0.587f;
			td->td_ycbcrcoeffs[2] = 0.114f;
		}
		*va_arg(ap, float **) = td->td_ycbcrcoeffs;
		return (1);
	case TIFFTAG_YCBCRSUBSAMPLING:
		*va_arg(ap, uint16 *) = td->td_ycbcrsubsampling[0];
		*va_arg(ap, uint16 *) = td->td_ycbcrsubsampling[1];
		return (1);
	case TIFFTAG_YCBCRPOSITIONING:
		*va_arg(ap, uint16 *) = td->td_ycbcrpositioning;
		return (1);
#endif
#ifdef COLORIMETRY_SUPPORT
	case TIFFTAG_TRANSFERFUNCTION:
		if (!td->td_transferfunction[0])
			TIFFDefaultTransferFunction(td);
		*va_arg(ap, uint16 **) = td->td_transferfunction[0];
		if (td->td_samplesperpixel - td->td_extrasamples > 1) {
			*va_arg(ap, uint16 **) = td->td_transferfunction[1];
			*va_arg(ap, uint16 **) = td->td_transferfunction[2];
		}
		return (1);
	case TIFFTAG_REFERENCEBLACKWHITE:
		if (!td->td_refblackwhite)
			TIFFDefaultRefBlackWhite(td);
		*va_arg(ap, float **) = td->td_refblackwhite;
		return (1);
#endif
	}
