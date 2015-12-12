#ifdef TT_CONFIG_OPTION_SUBPIXEL_HINTING
if ( !SUBPIXEL_HINTING  ||
         !CUR.ignore_x_mode )
#endif /* TT_CONFIG_OPTION_SUBPIXEL_HINTING */
      zone->cur[point].x += distance;
