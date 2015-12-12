#ifdef PNG_iTXt_SUPPORTED
if(textp->compression > 0)
      {
         textp->text_length = 0;
         textp->itxt_length = text_length;
      }
      else
#endif
      {
         textp->text_length = text_length;
#ifdef PNG_iTXt_SUPPORTED
         textp->itxt_length = 0;
#endif
      }
