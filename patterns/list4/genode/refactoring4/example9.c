#ifndef PNG_FREE_ME_SUPPORTED
if ((mask & PNG_FREE_PLTE) & info_ptr->free_me)
#else
if ((mask & PNG_FREE_PLTE) && (png_ptr->flags & PNG_FLAG_FREE_PLTE))
#endif
{
    png_zfree(png_ptr, info_ptr->palette);
    info_ptr->palette = NULL;
    info_ptr->valid &= ~PNG_INFO_PLTE;
#ifndef PNG_FREE_ME_SUPPORTED
    png_ptr->flags &= ~PNG_FLAG_FREE_PLTE;
#endif
    info_ptr->num_palette = 0;
}
