#ifdef TT_CONFIG_OPTION_SUBPIXEL_HINTING
if ( SUBPIXEL_HINTING         &&
           CUR.ignore_x_mode        &&
           CUR.GS.freeVector.x != 0 )
        distance = ROUND_None( distance,
                               CUR.tt_metrics.compensations[0] );
      else
#endif
        distance = CUR_Func_round( distance,
                                   CUR.tt_metrics.compensations[0] );
