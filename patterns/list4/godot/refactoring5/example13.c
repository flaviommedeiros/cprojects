#ifdef TT_CONFIG_OPTION_SUBPIXEL_HINTING
if ( SUBPIXEL_HINTING         &&
           CUR.ignore_x_mode        &&
           CUR.GS.freeVector.x != 0 )
        distance = ROUND_None(
                     org_dist,
                     CUR.tt_metrics.compensations[CUR.opcode & 3] );
      else
#endif
      distance = CUR_Func_round(
                   org_dist,
                   CUR.tt_metrics.compensations[CUR.opcode & 3] );
