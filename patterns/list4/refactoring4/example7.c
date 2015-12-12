#ifdef TT_CONFIG_OPTION_SUBPIXEL_HINTING
if ( !SUBPIXEL_HINTING                     ||
           ( !CUR.ignore_x_mode                ||
             !CUR.face->sph_compatibility_mode ) )
#endif /* TT_CONFIG_OPTION_SUBPIXEL_HINTING */
        CUR.zp0.org[point].x = TT_MulFix14( (FT_UInt32)distance,
                                            CUR.GS.freeVector.x );
