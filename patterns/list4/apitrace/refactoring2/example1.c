#  ifdef PNG_SETJMP_SUPPORTED
if (!setjmp(create_jmp_buf))
#  endif
      {
#  ifdef PNG_SETJMP_SUPPORTED
         /* Temporarily fake out the longjmp information until we have
          * successfully completed this function.  This only works if we have
          * setjmp() support compiled in, but it is safe - this stuff should
          * never happen.
          */
         create_struct.jmp_buf_ptr = &create_jmp_buf;
         create_struct.jmp_buf_size = 0; /*stack allocation*/
         create_struct.longjmp_fn = longjmp;
#  endif
         /* Call the general version checker (shared with read and write code):
          */
         if (png_user_version_check(&create_struct, user_png_ver) != 0)
         {
            png_structrp png_ptr = png_voidcast(png_structrp,
               png_malloc_warn(&create_struct, (sizeof *png_ptr)));

            if (png_ptr != NULL)
            {
               /* png_ptr->zstream holds a back-pointer to the png_struct, so
                * this can only be done now:
                */
               create_struct.zstream.zalloc = png_zalloc;
               create_struct.zstream.zfree = png_zfree;
               create_struct.zstream.opaque = png_ptr;

#              ifdef PNG_SETJMP_SUPPORTED
               /* Eliminate the local error handling: */
               create_struct.jmp_buf_ptr = NULL;
               create_struct.jmp_buf_size = 0;
               create_struct.longjmp_fn = 0;
#              endif

               *png_ptr = create_struct;

               /* This is the successful return point */
               return png_ptr;
            }
         }
      }
