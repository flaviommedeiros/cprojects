#ifdef HAVE_LIBZ
if (warc_current_gzfile)
    {
      warc_current_gzfile_uncompressed_size += size;
      return gzwrite (warc_current_gzfile, buffer, size);
    }
  else
#endif
    return fwrite (buffer, 1, size, warc_current_file);
