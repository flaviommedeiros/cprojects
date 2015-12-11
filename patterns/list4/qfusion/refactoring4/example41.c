#ifdef PNG_sPLT_SUPPORTED
if ((mask & PNG_FREE_SPLT) & info_ptr->free_me)
#else
   if (mask & PNG_FREE_SPLT)
#endif
   {
      if (num != -1)
      {
         if (info_ptr->splt_palettes)
         {
            png_free(png_ptr, info_ptr->splt_palettes[num].name);
            png_free(png_ptr, info_ptr->splt_palettes[num].entries);
            info_ptr->splt_palettes[num].name = NULL;
            info_ptr->splt_palettes[num].entries = NULL;
         }
      }
      else
      {
         if (info_ptr->splt_palettes_num)
         {
            int i;
            for (i = 0; i < (int)info_ptr->splt_palettes_num; i++)
               png_free_data(png_ptr, info_ptr, PNG_FREE_SPLT, i);

            png_free(png_ptr, info_ptr->splt_palettes);
            info_ptr->splt_palettes = NULL;
            info_ptr->splt_palettes_num = 0;
         }
         info_ptr->valid &= ~PNG_INFO_sPLT;
      }
   }
