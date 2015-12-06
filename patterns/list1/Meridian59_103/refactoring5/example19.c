#  ifdef PNG_USER_MEM_SUPPORTED
if (malloc_fn != NULL)
   {
      png_struct dummy_struct;
      png_memset(&dummy_struct, 0, sizeof dummy_struct);
      dummy_struct.mem_ptr=mem_ptr;
      struct_ptr = (*(malloc_fn))(&dummy_struct, (png_alloc_size_t)size);
   }

   else
#  endif /* PNG_USER_MEM_SUPPORTED */
   struct_ptr = (png_voidp)farmalloc(size);
