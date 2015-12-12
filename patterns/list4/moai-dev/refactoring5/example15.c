#ifdef PNG_USER_MEM_SUPPORTED
if (malloc_fn != NULL)
   {
      png_struct dummy_struct;
      png_structp png_ptr = &dummy_struct;
      png_ptr->mem_ptr=mem_ptr;
      struct_ptr = (*(malloc_fn))(png_ptr, (png_uint_32)size);
   }
   else
#endif /* PNG_USER_MEM_SUPPORTED */
   struct_ptr = (png_voidp)farmalloc(size);
