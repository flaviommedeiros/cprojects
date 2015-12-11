#ifdef PNG_FREE_ME_SUPPORTED
if ((mask & PNG_FREE_UNKN) & info_ptr->free_me)
#else
   if (mask & PNG_FREE_UNKN)
#endif
   {
      if (num != -1)
      {
          if (info_ptr->unknown_chunks)
          {
             png_free(png_ptr, info_ptr->unknown_chunks[num].data);
             info_ptr->unknown_chunks[num].data = NULL;
          }
      }
      else
      {
         int i;

         if (info_ptr->unknown_chunks_num)
         {
            for (i = 0; i < (int)info_ptr->unknown_chunks_num; i++)
               png_free_data(png_ptr, info_ptr, PNG_FREE_UNKN, i);

            png_free(png_ptr, info_ptr->unknown_chunks);
            info_ptr->unknown_chunks = NULL;
            info_ptr->unknown_chunks_num = 0;
         }
      }
   }
