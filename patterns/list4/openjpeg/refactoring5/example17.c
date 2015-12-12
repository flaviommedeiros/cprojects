#ifdef PNG_USER_MEM_SUPPORTED
if (png_ptr != NULL && png_ptr->malloc_fn != NULL)
         return png_ptr->malloc_fn(png_constcast(png_structrp,png_ptr), size);

      else
#endif
         return malloc((size_t)size);
