#if defined(PNG_tRNS_SUPPORTED)
if ((mask & PNG_FREE_TRNS) & info_ptr->free_me)
#else
if ((mask & PNG_FREE_TRNS) && (png_ptr->flags & PNG_FLAG_FREE_TRNS))
#endif
{
    png_free(png_ptr, info_ptr->trans);
    info_ptr->valid &= ~PNG_INFO_tRNS;
#ifndef PNG_FREE_ME_SUPPORTED
    png_ptr->flags &= ~PNG_FLAG_FREE_TRNS;
#endif
    info_ptr->trans = NULL;
}
