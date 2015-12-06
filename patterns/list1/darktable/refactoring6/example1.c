if(!strcasecmp(c, ".pfm") || !strcasecmp(c, ".hdr")
#ifdef HAVE_OPENEXR
       || !strcasecmp(c, ".exr")
#endif
           )
      return 1;
