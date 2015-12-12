#if defined(PNG_hIST_SUPPORTED)
if ((mask & PNG_FREE_HIST)  & info_ptr->free_me)
#else
if ((mask & PNG_FREE_HIST) && (png_ptr->flags & PNG_FLAG_FREE_HIST))
#endif
{
    png_free(png_ptr, info_ptr->hist);
    info_ptr->hist = NULL;
    info_ptr->valid &= ~PNG_INFO_hIST;
#ifndef PNG_FREE_ME_SUPPORTED
    png_ptr->flags &= ~PNG_FLAG_FREE_HIST;
#endif
}
