#ifdef PNG_FREE_ME_SUPPORTED
if ((mask & PNG_FREE_TEXT) & info_ptr->free_me)
#else
   if (mask & PNG_FREE_TEXT)
#endif
   {
      if (num != -1)
      {
         if (info_ptr->text && info_ptr->text[num].key)
         {
            png_free(png_ptr, info_ptr->text[num].key);
            info_ptr->text[num].key = NULL;
         }
      }
      else
      {
         int i;
         for (i = 0; i < info_ptr->num_text; i++)
             png_free_data(png_ptr, info_ptr, PNG_FREE_TEXT, i);
         png_free(png_ptr, info_ptr->text);
         info_ptr->text = NULL;
         info_ptr->num_text=0;
      }
   }
