#if defined(PNG_FIXED_POINT_SUPPORTED) && !defined(PNG_FLOATING_POINT_SUPPORTED)
if ((mask & PNG_FREE_PCAL) & info_ptr->free_me)
#else
   if (mask & PNG_FREE_PCAL)
#endif
   {
      png_free(png_ptr, info_ptr->pcal_purpose);
      png_free(png_ptr, info_ptr->pcal_units);
      info_ptr->pcal_purpose = NULL;
      info_ptr->pcal_units = NULL;
      if (info_ptr->pcal_params != NULL)
         {
            int i;
            for (i = 0; i < (int)info_ptr->pcal_nparams; i++)
            {
               png_free(png_ptr, info_ptr->pcal_params[i]);
               info_ptr->pcal_params[i] = NULL;
            }
            png_free(png_ptr, info_ptr->pcal_params);
            info_ptr->pcal_params = NULL;
         }
      info_ptr->valid &= ~PNG_INFO_pCAL;
   }
