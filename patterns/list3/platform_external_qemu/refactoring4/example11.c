#ifndef PNG_FREE_ME_SUPPORTED
if ((mask & PNG_FREE_ROWS) & info_ptr->free_me)
#else
if (mask & PNG_FREE_ROWS)
#endif
{
    if(info_ptr->row_pointers)
    {
       int row;
       for (row = 0; row < (int)info_ptr->height; row++)
       {
          png_free(png_ptr, info_ptr->row_pointers[row]);
          info_ptr->row_pointers[row]=NULL;
       }
       png_free(png_ptr, info_ptr->row_pointers);
       info_ptr->row_pointers=NULL;
    }
    info_ptr->valid &= ~PNG_INFO_IDAT;
}
