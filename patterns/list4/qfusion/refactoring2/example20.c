#ifndef PNG_READ_OPT_PLTE_SUPPORTED
if (png_ptr->color_type == PNG_COLOR_TYPE_PALETTE)
#endif
   {
      png_crc_finish(png_ptr, 0);
   }
#ifndef PNG_READ_OPT_PLTE_SUPPORTED
   else if (png_crc_error(png_ptr))  /* Only if we have a CRC error */
   {
      /* If we don't want to use the data from an ancillary chunk,
         we have two options: an error abort, or a warning and we
         ignore the data in this chunk (which should be OK, since
         it's considered ancillary for a RGB or RGBA image). */
      if (!(png_ptr->flags & PNG_FLAG_CRC_ANCILLARY_USE))
      {
         if (png_ptr->flags & PNG_FLAG_CRC_ANCILLARY_NOWARN)
         {
            png_chunk_error(png_ptr, "CRC error");
         }
         else
         {
            png_chunk_warning(png_ptr, "CRC error");
            return;
         }
      }
      /* Otherwise, we (optionally) emit a warning and use the chunk. */
      else if (!(png_ptr->flags & PNG_FLAG_CRC_ANCILLARY_NOWARN))
      {
         png_chunk_warning(png_ptr, "CRC error");
      }
   }
