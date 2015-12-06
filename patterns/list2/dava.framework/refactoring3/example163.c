switch (text->compression) {
#ifdef PNG_iTXt_SUPPORTED
            case PNG_ITXT_COMPRESSION_NONE:
            case PNG_ITXT_COMPRESSION_zTXt:
              text_length = text->itxt_length;
              break;
#endif
            case PNG_TEXT_COMPRESSION_NONE:
            case PNG_TEXT_COMPRESSION_zTXt:
            default:
              text_length = text->text_length;
              break;
          }
