switch ( glyph_format )
      {
      case 1:
      case 6:
        loader = tt_sbit_decoder_load_byte_aligned;
        break;

      case 2:
      case 5:
      case 7:
        loader = tt_sbit_decoder_load_bit_aligned;
        break;

      case 8:
        if ( p + 1 > p_limit )
          goto Fail;

        p += 1;  /* skip padding */
        /* fall-through */

      case 9:
        loader = tt_sbit_decoder_load_compound;
        break;

#ifdef FT_CONFIG_OPTION_USE_PNG
      case 17: /* small metrics, PNG image data   */
      case 18: /* big metrics, PNG image data     */
      case 19: /* metrics in EBLC, PNG image data */
        loader = tt_sbit_decoder_load_png;
        break;
#endif /* FT_CONFIG_OPTION_USE_PNG */

      default:
        error = FT_THROW( Invalid_Table );
        goto Fail;
      }
