#ifdef TT_CONFIG_OPTION_SUBPIXEL_HINTING
if ( driver->interpreter_version == TT_INTERPRETER_VERSION_38 )
      {
        /* a change from mono to subpixel rendering (and vice versa) */
        /* requires a re-execution of the CVT program                */
        if ( subpixel_hinting != exec->subpixel_hinting )
        {
          FT_TRACE4(( "tt_loader_init: subpixel hinting change,"
                      " re-executing `prep' table\n" ));

          exec->subpixel_hinting = subpixel_hinting;
          reexecute              = TRUE;
        }

        /* a change from mono to grayscale rendering (and vice versa) */
        /* requires a re-execution of the CVT program                 */
        if ( grayscale != exec->grayscale_hinting )
        {
          FT_TRACE4(( "tt_loader_init: grayscale hinting change,"
                      " re-executing `prep' table\n" ));

          exec->grayscale_hinting = grayscale_hinting;
          reexecute               = TRUE;
        }
      }
      else

#endif /* TT_CONFIG_OPTION_SUBPIXEL_HINTING */

      {
        /* a change from mono to grayscale rendering (and vice versa) */
        /* requires a re-execution of the CVT program                 */
        if ( grayscale != exec->grayscale )
        {
          FT_TRACE4(( "tt_loader_init: grayscale change,"
                      " re-executing `prep' table\n" ));

          exec->grayscale = grayscale;
          reexecute       = TRUE;
        }
      }
