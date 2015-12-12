#ifdef TT_CONFIG_OPTION_SUBPIXEL_HINTING
if ( SUBPIXEL_HINTING         &&
           CUR.ignore_x_mode        &&
           CUR.GS.freeVector.x != 0 )
        distance = ROUND_None(
                     cur_dist,
                     CUR.tt_metrics.compensations[0] ) - cur_dist;
      else
#endif
        distance = CUR_Func_round(
                     cur_dist,
                     CUR.tt_metrics.compensations[0] ) - cur_dist;
