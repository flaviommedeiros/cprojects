#ifdef HAVE_LIBPNG
if (png_screenshots)
    {
    WritePNGfile(lbmname, I_VideoBuffer,
                 SCREENWIDTH, SCREENHEIGHT,
                 W_CacheLumpName (DEH_String("PLAYPAL"), PU_CACHE));
    }
    else
#endif
    {
    // save the pcx file
    WritePCXfile(lbmname, I_VideoBuffer,
                 SCREENWIDTH, SCREENHEIGHT,
                 W_CacheLumpName (DEH_String("PLAYPAL"), PU_CACHE));
    }
