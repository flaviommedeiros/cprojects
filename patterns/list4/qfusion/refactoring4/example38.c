#ifndef PNG_FREE_ME_SUPPORTED
if ((mask & PNG_FREE_SCAL) & info_ptr->free_me)
#else
   if (mask & PNG_FREE_SCAL)
#endif
   {
#if defined(PNG_FIXED_POINT_SUPPORTED) && !defined(PNG_FLOATING_POINT_SUPPORTED)
      png_free(png_ptr, info_ptr->scal_s_width);
      png_free(png_ptr, info_ptr->scal_s_height);
      info_ptr->scal_s_width = NULL;
      info_ptr->scal_s_height = NULL;
#endif
      info_ptr->valid &= ~PNG_INFO_sCAL;
   }
