#ifdef PNG_MMX_READ_FILTER_UP_SUPPORTED
if ((png_ptr->asm_flags & PNG_ASM_FLAG_MMX_READ_FILTER_UP) &&
             (row_info->pixel_depth >= png_ptr->mmx_bitdepth_threshold) &&
             (row_info->rowbytes >= png_ptr->mmx_rowbytes_threshold))
#else
         if (_mmx_supported)
#endif
         {
            png_read_filter_row_mmx_up(row_info, row, prev_row);
         }
          else
#endif
         {
            png_uint_32 i;
            png_uint_32 istop = row_info->rowbytes;
            png_bytep rp = row;
            png_bytep pp = prev_row;

            for (i = 0; i < istop; ++i)
            {
               *rp = (png_byte)(((int)(*rp) + (int)(*pp++)) & 0xff);
               rp++;
            }
         }
