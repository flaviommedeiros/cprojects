switch (dp->tdir_tag) {
		case TIFFTAG_MINSAMPLEVALUE:
		case TIFFTAG_MAXSAMPLEVALUE:
		case TIFFTAG_BITSPERSAMPLE:
			/*
			 * The 5.0 spec says the Compression tag has
			 * one value, while earlier specs say it has
			 * one value per sample.  Because of this, we
			 * accept the tag if one value is supplied.
			 *
			 * The MinSampleValue, MaxSampleValue and
			 * BitsPerSample tags are supposed to be written
			 * as one value/sample, but some vendors incorrectly
			 * write one value only -- so we accept that
			 * as well (yech).
			 */
			if (dp->tdir_count == 1) {
				v = TIFFExtractData(tif,
				    dp->tdir_type, dp->tdir_offset);
				if (!TIFFSetField(tif, dp->tdir_tag, (int)v))
					goto bad;
				break;
			}
			/* fall thru... */
		case TIFFTAG_DATATYPE:
		case TIFFTAG_SAMPLEFORMAT:
			if (!TIFFFetchPerSampleShorts(tif, dp, &iv) ||
			    !TIFFSetField(tif, dp->tdir_tag, iv))
				goto bad;
			break;
		case TIFFTAG_SMINSAMPLEVALUE:
		case TIFFTAG_SMAXSAMPLEVALUE:
			if (!TIFFFetchPerSampleAnys(tif, dp, &dv) ||
			    !TIFFSetField(tif, dp->tdir_tag, dv))
				goto bad;
			break;
		case TIFFTAG_STRIPOFFSETS:
		case TIFFTAG_TILEOFFSETS:
			if (!TIFFFetchStripThing(tif, dp,
			    td->td_nstrips, &td->td_stripoffset))
				goto bad;
			break;
		case TIFFTAG_STRIPBYTECOUNTS:
		case TIFFTAG_TILEBYTECOUNTS:
			if (!TIFFFetchStripThing(tif, dp,
			    td->td_nstrips, &td->td_stripbytecount))
				goto bad;
			break;
		case TIFFTAG_COLORMAP:
		case TIFFTAG_TRANSFERFUNCTION:
			/*
			 * TransferFunction can have either 1x or 3x data
			 * values; Colormap can have only 3x items.
			 */
			v = 1L<<td->td_bitspersample;
			if (dp->tdir_tag == TIFFTAG_COLORMAP ||
			    dp->tdir_count != (uint32) v) {
				if (!CheckDirCount(tif, dp, (uint32)(3*v)))
					break;
			}
			v *= sizeof (uint16);
			cp = CheckMalloc(tif, dp->tdir_count * sizeof (uint16),
			    "to read \"TransferFunction\" tag");
			if (cp != NULL) {
				if (TIFFFetchData(tif, dp, cp)) {
					/*
					 * This deals with there being only
					 * one array to apply to all samples.
					 */
					uint32 c =
					    (uint32)1 << td->td_bitspersample;
					if (dp->tdir_count == c)
						v = 0;
					TIFFSetField(tif, dp->tdir_tag,
					    cp, cp+v, cp+2*v);
				}
				_TIFFfree(cp);
			}
			break;
		case TIFFTAG_PAGENUMBER:
		case TIFFTAG_HALFTONEHINTS:
		case TIFFTAG_YCBCRSUBSAMPLING:
		case TIFFTAG_DOTRANGE:
			(void) TIFFFetchShortPair(tif, dp);
			break;
#ifdef COLORIMETRY_SUPPORT
		case TIFFTAG_REFERENCEBLACKWHITE:
			(void) TIFFFetchRefBlackWhite(tif, dp);
			break;
#endif
/* BEGIN REV 4.0 COMPATIBILITY */
		case TIFFTAG_OSUBFILETYPE:
			v = 0;
			switch (TIFFExtractData(tif, dp->tdir_type,
			    dp->tdir_offset)) {
			case OFILETYPE_REDUCEDIMAGE:
				v = FILETYPE_REDUCEDIMAGE;
				break;
			case OFILETYPE_PAGE:
				v = FILETYPE_PAGE;
				break;
			}
			if (v)
				(void) TIFFSetField(tif,
				    TIFFTAG_SUBFILETYPE, (int)v);
			break;
/* END REV 4.0 COMPATIBILITY */
		default:
			(void) TIFFFetchNormalTag(tif, dp);
			break;
		}
