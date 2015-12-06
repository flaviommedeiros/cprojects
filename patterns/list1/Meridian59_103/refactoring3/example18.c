switch (bit_depth)
      {
         default:
         /* Must be 1bpp gray: should not be here! */
            /* NOTREACHED */
            break;

         case 2:
         /* Must be 2bpp gray */
         /* assert(channels == 1 && shift[0] == 1) */
         {
            png_bytep bp = row;
            png_bytep bp_end = bp + row_info->rowbytes;

            while (bp < bp_end)
            {
               int b = (*bp >> 1) & 0x55;
               *bp++ = (png_byte)b;
            }
            break;
         }

         case 4:
         /* Must be 4bpp gray */
         /* assert(channels == 1) */
         {
            png_bytep bp = row;
            png_bytep bp_end = bp + row_info->rowbytes;
            int gray_shift = shift[0];
            int mask =  0xf >> gray_shift;

            mask |= mask << 4;

            while (bp < bp_end)
            {
               int b = (*bp >> gray_shift) & mask;
               *bp++ = (png_byte)b;
            }
            break;
         }

         case 8:
         /* Single byte components, G, GA, RGB, RGBA */
         {
            png_bytep bp = row;
            png_bytep bp_end = bp + row_info->rowbytes;
            int channel = 0;

            while (bp < bp_end)
            {
               int b = *bp >> shift[channel];
               if (++channel >= channels)
                  channel = 0;
               *bp++ = (png_byte)b;
            }
            break;
         }

#ifdef PNG_READ_16BIT_SUPPORTED
         case 16:
         /* Double byte components, G, GA, RGB, RGBA */
         {
            png_bytep bp = row;
            png_bytep bp_end = bp + row_info->rowbytes;
            int channel = 0;

            while (bp < bp_end)
            {
               int value = (bp[0] << 8) + bp[1];

               value >>= shift[channel];
               if (++channel >= channels)
                  channel = 0;
               *bp++ = (png_byte)(value >> 8);
               *bp++ = (png_byte)(value & 0xff);
            }
            break;
         }
#endif
      }
