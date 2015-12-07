switch (fip->field_bit) {
		case FIELD_STRIPOFFSETS:
			/*
			 * We use one field bit for both strip and tile
			 * offsets, and so must be careful in selecting
			 * the appropriate field descriptor (so that tags
			 * are written in sorted order).
			 */
			tag = isTiled(tif) ?
			    TIFFTAG_TILEOFFSETS : TIFFTAG_STRIPOFFSETS;
			if (tag != fip->field_tag)
				continue;
			if (!TIFFWriteLongArray(tif, TIFF_LONG, tag, dir,
			    (uint32) td->td_nstrips, td->td_stripoffset))
				goto bad;
			break;
		case FIELD_STRIPBYTECOUNTS:
			/*
			 * We use one field bit for both strip and tile
			 * byte counts, and so must be careful in selecting
			 * the appropriate field descriptor (so that tags
			 * are written in sorted order).
			 */
			tag = isTiled(tif) ?
			    TIFFTAG_TILEBYTECOUNTS : TIFFTAG_STRIPBYTECOUNTS;
			if (tag != fip->field_tag)
				continue;
			if (!TIFFWriteLongArray(tif, TIFF_LONG, tag, dir,
			    (uint32) td->td_nstrips, td->td_stripbytecount))
				goto bad;
			break;
		case FIELD_ROWSPERSTRIP:
			TIFFSetupShortLong(tif, TIFFTAG_ROWSPERSTRIP,
			    dir, td->td_rowsperstrip);
			break;
		case FIELD_COLORMAP:
			if (!TIFFWriteShortTable(tif, TIFFTAG_COLORMAP, dir,
			    3, td->td_colormap))
				goto bad;
			break;
		case FIELD_IMAGEDIMENSIONS:
			TIFFSetupShortLong(tif, TIFFTAG_IMAGEWIDTH,
			    dir++, td->td_imagewidth);
			TIFFSetupShortLong(tif, TIFFTAG_IMAGELENGTH,
			    dir, td->td_imagelength);
			break;
		case FIELD_TILEDIMENSIONS:
			TIFFSetupShortLong(tif, TIFFTAG_TILEWIDTH,
			    dir++, td->td_tilewidth);
			TIFFSetupShortLong(tif, TIFFTAG_TILELENGTH,
			    dir, td->td_tilelength);
			break;
		case FIELD_POSITION:
			WriteRationalPair(TIFF_RATIONAL,
			    TIFFTAG_XPOSITION, td->td_xposition,
			    TIFFTAG_YPOSITION, td->td_yposition);
			break;
		case FIELD_RESOLUTION:
			WriteRationalPair(TIFF_RATIONAL,
			    TIFFTAG_XRESOLUTION, td->td_xresolution,
			    TIFFTAG_YRESOLUTION, td->td_yresolution);
			break;
		case FIELD_BITSPERSAMPLE:
		case FIELD_MINSAMPLEVALUE:
		case FIELD_MAXSAMPLEVALUE:
		case FIELD_SAMPLEFORMAT:
			if (!TIFFWritePerSampleShorts(tif, fip->field_tag, dir))
				goto bad;
			break;
		case FIELD_SMINSAMPLEVALUE:
		case FIELD_SMAXSAMPLEVALUE:
			if (!TIFFWritePerSampleAnys(tif,
			    _TIFFSampleToTagType(tif), fip->field_tag, dir))
				goto bad;
			break;
		case FIELD_PAGENUMBER:
		case FIELD_HALFTONEHINTS:
#ifdef YCBCR_SUPPORT
		case FIELD_YCBCRSUBSAMPLING:
#endif
#ifdef CMYK_SUPPORT
		case FIELD_DOTRANGE:
#endif
			if (!TIFFSetupShortPair(tif, fip->field_tag, dir))
				goto bad;
			break;
#ifdef CMYK_SUPPORT
		case FIELD_INKNAMES:
			if (!TIFFWriteInkNames(tif, dir))
				goto bad;
			break;
#endif
#ifdef COLORIMETRY_SUPPORT
		case FIELD_TRANSFERFUNCTION:
			if (!TIFFWriteTransferFunction(tif, dir))
				goto bad;
			break;
#endif
#if SUBIFD_SUPPORT
		case FIELD_SUBIFD:
			if (!TIFFWriteNormalTag(tif, dir, fip))
				goto bad;
			/*
			 * Total hack: if this directory includes a SubIFD
			 * tag then force the next <n> directories to be
			 * written as ``sub directories'' of this one.  This
			 * is used to write things like thumbnails and
			 * image masks that one wants to keep out of the
			 * normal directory linkage access mechanism.
			 */
			if (dir->tdir_count > 0) {
				tif->tif_flags |= TIFF_INSUBIFD;
				tif->tif_nsubifd = (uint16) dir->tdir_count;
				if (dir->tdir_count > 1)
					tif->tif_subifdoff = dir->tdir_offset;
				else
					tif->tif_subifdoff = (uint32)(
					      tif->tif_diroff
					    + sizeof (uint16)
					    + ((char*)&dir->tdir_offset-data));
			}
			break;
#endif
		default:
			if (!TIFFWriteNormalTag(tif, dir, fip))
				goto bad;
			break;
		}
