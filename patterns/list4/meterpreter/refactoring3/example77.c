switch ((compptr->DCT_h_scaled_size << 8) + compptr->DCT_v_scaled_size) {
#ifdef IDCT_SCALING_SUPPORTED
    case ((1 << 8) + 1):
      method_ptr = jpeg_idct_1x1;
      method = JDCT_ISLOW;	/* jidctint uses islow-style table */
      break;
    case ((2 << 8) + 2):
      method_ptr = jpeg_idct_2x2;
      method = JDCT_ISLOW;	/* jidctint uses islow-style table */
      break;
    case ((3 << 8) + 3):
      method_ptr = jpeg_idct_3x3;
      method = JDCT_ISLOW;	/* jidctint uses islow-style table */
      break;
    case ((4 << 8) + 4):
      method_ptr = jpeg_idct_4x4;
      method = JDCT_ISLOW;	/* jidctint uses islow-style table */
      break;
    case ((5 << 8) + 5):
      method_ptr = jpeg_idct_5x5;
      method = JDCT_ISLOW;	/* jidctint uses islow-style table */
      break;
    case ((6 << 8) + 6):
      method_ptr = jpeg_idct_6x6;
      method = JDCT_ISLOW;	/* jidctint uses islow-style table */
      break;
    case ((7 << 8) + 7):
      method_ptr = jpeg_idct_7x7;
      method = JDCT_ISLOW;	/* jidctint uses islow-style table */
      break;
    case ((9 << 8) + 9):
      method_ptr = jpeg_idct_9x9;
      method = JDCT_ISLOW;	/* jidctint uses islow-style table */
      break;
    case ((10 << 8) + 10):
      method_ptr = jpeg_idct_10x10;
      method = JDCT_ISLOW;	/* jidctint uses islow-style table */
      break;
    case ((11 << 8) + 11):
      method_ptr = jpeg_idct_11x11;
      method = JDCT_ISLOW;	/* jidctint uses islow-style table */
      break;
    case ((12 << 8) + 12):
      method_ptr = jpeg_idct_12x12;
      method = JDCT_ISLOW;	/* jidctint uses islow-style table */
      break;
    case ((13 << 8) + 13):
      method_ptr = jpeg_idct_13x13;
      method = JDCT_ISLOW;	/* jidctint uses islow-style table */
      break;
    case ((14 << 8) + 14):
      method_ptr = jpeg_idct_14x14;
      method = JDCT_ISLOW;	/* jidctint uses islow-style table */
      break;
    case ((15 << 8) + 15):
      method_ptr = jpeg_idct_15x15;
      method = JDCT_ISLOW;	/* jidctint uses islow-style table */
      break;
    case ((16 << 8) + 16):
      method_ptr = jpeg_idct_16x16;
      method = JDCT_ISLOW;	/* jidctint uses islow-style table */
      break;
    case ((16 << 8) + 8):
      method_ptr = jpeg_idct_16x8;
      method = JDCT_ISLOW;	/* jidctint uses islow-style table */
      break;
    case ((14 << 8) + 7):
      method_ptr = jpeg_idct_14x7;
      method = JDCT_ISLOW;	/* jidctint uses islow-style table */
      break;
    case ((12 << 8) + 6):
      method_ptr = jpeg_idct_12x6;
      method = JDCT_ISLOW;	/* jidctint uses islow-style table */
      break;
    case ((10 << 8) + 5):
      method_ptr = jpeg_idct_10x5;
      method = JDCT_ISLOW;	/* jidctint uses islow-style table */
      break;
    case ((8 << 8) + 4):
      method_ptr = jpeg_idct_8x4;
      method = JDCT_ISLOW;	/* jidctint uses islow-style table */
      break;
    case ((6 << 8) + 3):
      method_ptr = jpeg_idct_6x3;
      method = JDCT_ISLOW;	/* jidctint uses islow-style table */
      break;
    case ((4 << 8) + 2):
      method_ptr = jpeg_idct_4x2;
      method = JDCT_ISLOW;	/* jidctint uses islow-style table */
      break;
    case ((2 << 8) + 1):
      method_ptr = jpeg_idct_2x1;
      method = JDCT_ISLOW;	/* jidctint uses islow-style table */
      break;
    case ((8 << 8) + 16):
      method_ptr = jpeg_idct_8x16;
      method = JDCT_ISLOW;	/* jidctint uses islow-style table */
      break;
    case ((7 << 8) + 14):
      method_ptr = jpeg_idct_7x14;
      method = JDCT_ISLOW;	/* jidctint uses islow-style table */
      break;
    case ((6 << 8) + 12):
      method_ptr = jpeg_idct_6x12;
      method = JDCT_ISLOW;	/* jidctint uses islow-style table */
      break;
    case ((5 << 8) + 10):
      method_ptr = jpeg_idct_5x10;
      method = JDCT_ISLOW;	/* jidctint uses islow-style table */
      break;
    case ((4 << 8) + 8):
      method_ptr = jpeg_idct_4x8;
      method = JDCT_ISLOW;	/* jidctint uses islow-style table */
      break;
    case ((3 << 8) + 6):
      method_ptr = jpeg_idct_3x6;
      method = JDCT_ISLOW;	/* jidctint uses islow-style table */
      break;
    case ((2 << 8) + 4):
      method_ptr = jpeg_idct_2x4;
      method = JDCT_ISLOW;	/* jidctint uses islow-style table */
      break;
    case ((1 << 8) + 2):
      method_ptr = jpeg_idct_1x2;
      method = JDCT_ISLOW;	/* jidctint uses islow-style table */
      break;
#endif
    case ((DCTSIZE << 8) + DCTSIZE):
      switch (cinfo->dct_method) {
#ifdef DCT_ISLOW_SUPPORTED
      case JDCT_ISLOW:
	method_ptr = jpeg_idct_islow;
	method = JDCT_ISLOW;
	break;
#endif
#ifdef DCT_IFAST_SUPPORTED
      case JDCT_IFAST:
	method_ptr = jpeg_idct_ifast;
	method = JDCT_IFAST;
	break;
#endif
#ifdef DCT_FLOAT_SUPPORTED
      case JDCT_FLOAT:
	method_ptr = jpeg_idct_float;
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
