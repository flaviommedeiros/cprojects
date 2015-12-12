switch (png_ptr->process_mode)
   {
      case PNG_READ_SIG_MODE:
      {
         png_push_read_sig(png_ptr, info_ptr);
         break;
      }

      case PNG_READ_CHUNK_MODE:
      {
         png_push_read_chunk(png_ptr, info_ptr);
         break;
      }

      case PNG_READ_IDAT_MODE:
      {
         png_push_read_IDAT(png_ptr);
         break;
      }

#ifdef PNG_READ_tEXt_SUPPORTED
      case PNG_READ_tEXt_MODE:
      {
         png_push_read_tEXt(png_ptr, info_ptr);
         break;
      }

#endif
#ifdef PNG_READ_zTXt_SUPPORTED
      case PNG_READ_zTXt_MODE:
      {
         png_push_read_zTXt(png_ptr, info_ptr);
         break;
      }

#endif
#ifdef PNG_READ_iTXt_SUPPORTED
      case PNG_READ_iTXt_MODE:
      {
         png_push_read_iTXt(png_ptr, info_ptr);
         break;
      }

#endif
      case PNG_SKIP_MODE:
      {
         png_push_crc_finish(png_ptr);
         break;
      }

      default:
      {
         png_ptr->buffer_size = 0;
         break;
      }
   }
