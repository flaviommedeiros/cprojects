#ifdef TT_CONFIG_OPTION_SUBPIXEL_HINTING
if ( !SUBPIXEL_HINTING                                     ||
           ( !CUR.ignore_x_mode                                ||
             ( CUR.sph_tweak_flags & SPH_TWEAK_ALLOW_X_DMOVE ) ) )
#endif /* TT_CONFIG_OPTION_SUBPIXEL_HINTING */
        zone->cur[point].x += FT_MulDiv( distance, v, CUR.F_dot_P );
