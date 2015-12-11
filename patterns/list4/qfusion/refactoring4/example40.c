#ifdef PNG_iCCP_SUPPORTED
if ((mask & PNG_FREE_ICCP) & info_ptr->free_me)
#else
   if (mask & PNG_FREE_ICCP)
#endif
   {
      png_free(png_ptr, info_ptr->iccp_name);
      png_free(png_ptr, info_ptr->iccp_profile);
      info_ptr->iccp_name = NULL;
      info_ptr->iccp_profile = NULL;
      info_ptr->valid &= ~PNG_INFO_iCCP;
   }
