#     ifdef PNG_SIMPLIFIED_WRITE_AFIRST_SUPPORTED
if ((image->format & PNG_FORMAT_FLAG_AFIRST) != 0)
         {
            aindex = -1;
            ++input_row; /* To point to the first component */
            ++output_row;
         }

         else
#     endif
         aindex = channels;
