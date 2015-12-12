switch ((compptr->DCT_h_scaled_size << 8) + compptr->DCT_v_scaled_size) {
#ifdef DCT_SCALING_SUPPORTED
    case ((1 << 8) + 1):
      fdct->do_dct[ci] = jpeg_fdct_1x1;
      method = JDCT_ISLOW;	/* jfdctint uses islow-style table */
      break;
    case ((2 << 8) + 2):
      fdct->do_dct[ci] = jpeg_fdct_2x2;
      method = JDCT_ISLOW;	/* jfdctint uses islow-style table */
      break;
    case ((3 << 8) + 3):
      fdct->do_dct[ci] = jpeg_fdct_3x3;
      method = JDCT_ISLOW;	/* jfdctint uses islow-style table */
      break;
    case ((4 << 8) + 4):
      fdct->do_dct[ci] = jpeg_fdct_4x4;
      method = JDCT_ISLOW;	/* jfdctint uses islow-style table */
      break;
    case ((5 << 8) + 5):
      fdct->do_dct[ci] = jpeg_fdct_5x5;
      method = JDCT_ISLOW;	/* jfdctint uses islow-style table */
      break;
    case ((6 << 8) + 6):
      fdct->do_dct[ci] = jpeg_fdct_6x6;
      method = JDCT_ISLOW;	/* jfdctint uses islow-style table */
      break;
    case ((7 << 8) + 7):
      fdct->do_dct[ci] = jpeg_fdct_7x7;
      method = JDCT_ISLOW;	/* jfdctint uses islow-style table */
      break;
    case ((9 << 8) + 9):
      fdct->do_dct[ci] = jpeg_fdct_9x9;
      method = JDCT_ISLOW;	/* jfdctint uses islow-style table */
      break;
    case ((10 << 8) + 10):
      fdct->do_dct[ci] = jpeg_fdct_10x10;
      method = JDCT_ISLOW;	/* jfdctint uses islow-style table */
      break;
    case ((11 << 8) + 11):
      fdct->do_dct[ci] = jpeg_fdct_11x11;
      method = JDCT_ISLOW;	/* jfdctint uses islow-style table */
      break;
    case ((12 << 8) + 12):
      fdct->do_dct[ci] = jpeg_fdct_12x12;
      method = JDCT_ISLOW;	/* jfdctint uses islow-style table */
      break;
    case ((13 << 8) + 13):
      fdct->do_dct[ci] = jpeg_fdct_13x13;
      method = JDCT_ISLOW;	/* jfdctint uses islow-style table */
      break;
    case ((14 << 8) + 14):
      fdct->do_dct[ci] = jpeg_fdct_14x14;
      method = JDCT_ISLOW;	/* jfdctint uses islow-style table */
      break;
    case ((15 << 8) + 15):
      fdct->do_dct[ci] = jpeg_fdct_15x15;
      method = JDCT_ISLOW;	/* jfdctint uses islow-style table */
      break;
    case ((16 << 8) + 16):
      fdct->do_dct[ci] = jpeg_fdct_16x16;
      method = JDCT_ISLOW;	/* jfdctint uses islow-style table */
      break;
    case ((16 << 8) + 8):
      fdct->do_dct[ci] = jpeg_fdct_16x8;
      method = JDCT_ISLOW;	/* jfdctint uses islow-style table */
      break;
    case ((14 << 8) + 7):
      fdct->do_dct[ci] = jpeg_fdct_14x7;
      method = JDCT_ISLOW;	/* jfdctint uses islow-style table */
      break;
    case ((12 << 8) + 6):
      fdct->do_dct[ci] = jpeg_fdct_12x6;
      method = JDCT_ISLOW;	/* jfdctint uses islow-style table */
      break;
    case ((10 << 8) + 5):
      fdct->do_dct[ci] = jpeg_fdct_10x5;
      method = JDCT_ISLOW;	/* jfdctint uses islow-style table */
      break;
    case ((8 << 8) + 4):
      fdct->do_dct[ci] = jpeg_fdct_8x4;
      method = JDCT_ISLOW;	/* jfdctint uses islow-style table */
      break;
    case ((6 << 8) + 3):
      fdct->do_dct[ci] = jpeg_fdct_6x3;
      method = JDCT_ISLOW;	/* jfdctint uses islow-style table */
      break;
    case ((4 << 8) + 2):
      fdct->do_dct[ci] = jpeg_fdct_4x2;
      method = JDCT_ISLOW;	/* jfdctint uses islow-style table */
      break;
    case ((2 << 8) + 1):
      fdct->do_dct[ci] = jpeg_fdct_2x1;
      method = JDCT_ISLOW;	/* jfdctint uses islow-style table */
      break;
    case ((8 << 8) + 16):
      fdct->do_dct[ci] = jpeg_fdct_8x16;
      method = JDCT_ISLOW;	/* jfdctint uses islow-style table */
      break;
    case ((7 << 8) + 14):
      fdct->do_dct[ci] = jpeg_fdct_7x14;
      method = JDCT_ISLOW;	/* jfdctint uses islow-style table */
      break;
    case ((6 << 8) + 12):
      fdct->do_dct[ci] = jpeg_fdct_6x12;
      method = JDCT_ISLOW;	/* jfdctint uses islow-style table */
      break;
    case ((5 << 8) + 10):
      fdct->do_dct[ci] = jpeg_fdct_5x10;
      method = JDCT_ISLOW;	/* jfdctint uses islow-style table */
      break;
    case ((4 << 8) + 8):
      fdct->do_dct[ci] = jpeg_fdct_4x8;
      method = JDCT_ISLOW;	/* jfdctint uses islow-style table */
      break;
    case ((3 << 8) + 6):
      fdct->do_dct[ci] = jpeg_fdct_3x6;
      method = JDCT_ISLOW;	/* jfdctint uses islow-style table */
      break;
    case ((2 << 8) + 4):
      fdct->do_dct[ci] = jpeg_fdct_2x4;
      method = JDCT_ISLOW;	/* jfdctint uses islow-style table */
      break;
    case ((1 << 8) + 2):
      fdct->do_dct[ci] = jpeg_fdct_1x2;
      method = JDCT_ISLOW;	/* jfdctint uses islow-style table */
      break;
#endif
    case ((DCTSIZE << 8) + DCTSIZE):
      switch (cinfo->dct_method) {
#ifdef DCT_ISLOW_SUPPORTED
      case JDCT_ISLOW:
	fdct->do_dct[ci] = jpeg_fdct_islow;
	method = JDCT_ISLOW;
	break;
#endif
#ifdef DCT_IFAST_SUPPORTED
      case JDCT_IFAST:
	fdct->do_dct[ci] = jpeg_fdct_ifast;
	method = JDCT_IFAST;
	break;
#endif
#ifdef DCT_FLOAT_SUPPORTED
      case JDCT_FLOAT:
	fdct->do_float_dct[ci] = jpeg_fdct_float;
	method = JDCT_FLOAT;
	break;
#endif
      default:
	ERREXIT(cinfo, JERR_NOT_COMPILED);
	break;
      }
      break;
    default:
      ERREXIT2(cinfo, JERR_BAD_DCTSIZE,
	       compptr->DCT_h_scaled_size, compptr->DCT_v_scaled_size);
      break;
    }
