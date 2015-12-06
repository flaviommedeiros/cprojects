#  ifdef PNG_iTXt_SUPPORTED
if (text_ptr[i].compression > 0)
            textp->compression = PNG_ITXT_COMPRESSION_NONE;

         else
#  endif
            textp->compression = PNG_TEXT_COMPRESSION_NONE;
