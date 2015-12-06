#ifdef TT_CONFIG_OPTION_UNPATENTED_HINTING
if ( CUR.face->unpatented_hinting )
      {
        if ( CUR.GS.both_x_axis )
          CUR.tt_metrics.ratio = CUR.tt_metrics.x_ratio;
        else
          CUR.tt_metrics.ratio = CUR.tt_metrics.y_ratio;
      }
      else
#endif
      {
        if ( CUR.GS.projVector.y == 0 )
          CUR.tt_metrics.ratio = CUR.tt_metrics.x_ratio;

        else if ( CUR.GS.projVector.x == 0 )
          CUR.tt_metrics.ratio = CUR.tt_metrics.y_ratio;

        else
        {
          FT_Long  x, y;


          x = TT_MULDIV( CUR.GS.projVector.x,
                         CUR.tt_metrics.x_ratio, 0x4000 );
          y = TT_MULDIV( CUR.GS.projVector.y,
                         CUR.tt_metrics.y_ratio, 0x4000 );
          CUR.tt_metrics.ratio = TT_VecLen( x, y );
        }
      }
