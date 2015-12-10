#ifdef PNG_MMX_READ_FILTER_AVG_SUPPORTED
if ((png_ptr->asm_flags & PNG_ASM_FLAG_MMX_READ_FILTER_AVG) &&
             (row_info->pixel_depth >= png_ptr->mmx_bitdepth_threshold) &&
             (row_info->rowbytes >= png_ptr->mmx_rowbytes_threshold))
#else
         if (_mmx_supported)
#endif
         {
            png_read_filter_row_mmx_avg(row_info, row, prev_row);
         }
         else
#endif
         {
            png_uint_32 i;
            png_bytep rp = row;
            png_bytep pp = prev_row;
            png_bytep lp = row;
            png_uint_32 bpp = (row_info->pixel_depth + 7) >> 3;
            png_uint_32 istop = row_info->rowbytes - bpp;

            for (i = 0; i < bpp; i++)
            {
               *rp = (png_byte)(((int)(*rp) +
                  ((int)(*pp++) >> 1)) & 0xff);
               rp++;
            }

            for (i = 0; i < istop; i++)
            {
               *rp = (png_byte)(((int)(*rp) +
                  ((int)(*pp++ + *lp++) >> 1)) & 0xff);
               rp++;
            }
         }
