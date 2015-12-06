if ((err==UNZ_OK) && (s->cur_file_info.compression_method!=0) &&
         /* #ifdef HAVE_BZIP2 */
         (s->cur_file_info.compression_method!=Z_BZIP2ED) &&
         /* #endif */
         (s->cur_file_info.compression_method!=Z_DEFLATED))
      err=UNZ_BADZIPFILE;
