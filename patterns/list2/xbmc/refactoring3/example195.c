switch ( subr_no )
        {
        case 1:                     /* start flex feature */
          if ( arg_cnt != 0 )
            goto Unexpected_OtherSubr;

          decoder->flex_state        = 1;
          decoder->num_flex_vectors  = 0;
          if ( start_point( builder, x, y ) ||
               check_points( builder, 6 )   )
            goto Fail;
          break;

        case 2:                     /* add flex vectors */
          {
            FT_Int  idx;


            if ( arg_cnt != 0 )
              goto Unexpected_OtherSubr;

            /* note that we should not add a point for index 0; */
            /* this will move our current position to the flex  */
            /* point without adding any point to the outline    */
            idx = decoder->num_flex_vectors++;
            if ( idx > 0 && idx < 7 )
              add_point( builder,
                         x,
                         y,
                         (FT_Byte)( idx == 3 || idx == 6 ) );
          }
          break;

        case 0:                     /* end flex feature */
          if ( arg_cnt != 3 )
            goto Unexpected_OtherSubr;

          if ( decoder->flex_state       == 0 ||
               decoder->num_flex_vectors != 7 )
          {
            FT_ERROR(( "t1_decoder_parse_charstrings: "
                       "unexpected flex end\n" ));
            goto Syntax_Error;
          }

          /* the two `results' are popped by the following setcurrentpoint */
          known_othersubr_result_cnt = 2;
          break;

        case 3:                     /* change hints */
          if ( arg_cnt != 1 )
            goto Unexpected_OtherSubr;

          known_othersubr_result_cnt = 1;

          if ( hinter )
            hinter->reset( hinter->hints, builder->current->n_points );

          break;

        case 12:
        case 13:
          /* counter control hints, clear stack */
          top = decoder->stack;
          break;

        case 14:
        case 15:
        case 16:
        case 17:
        case 18:                    /* multiple masters */
          {
            PS_Blend  blend = decoder->blend;
            FT_UInt   num_points, nn, mm;
            FT_Long*  delta;
            FT_Long*  values;


            if ( !blend )
            {
              FT_ERROR(( "t1_decoder_parse_charstrings: " ));
              FT_ERROR(( "unexpected multiple masters operator!\n" ));
              goto Syntax_Error;
            }

            num_points = (FT_UInt)subr_no - 13 + ( subr_no == 18 );
            if ( arg_cnt != (FT_Int)( num_points * blend->num_designs ) )
            {
              FT_ERROR(( "t1_decoder_parse_charstrings: " ));
              FT_ERROR(( "incorrect number of mm arguments\n" ));
              goto Syntax_Error;
            }

            /* we want to compute:                                   */
            /*                                                       */
            /*  a0*w0 + a1*w1 + ... + ak*wk                          */
            /*                                                       */
            /* but we only have the a0, a1-a0, a2-a0, .. ak-a0       */
            /* however, given that w0 + w1 + ... + wk == 1, we can   */
            /* rewrite it easily as:                                 */
            /*                                                       */
            /*  a0 + (a1-a0)*w1 + (a2-a0)*w2 + .. + (ak-a0)*wk       */
            /*                                                       */
            /* where k == num_designs-1                              */
            /*                                                       */
            /* I guess that's why it's written in this `compact'     */
            /* form.                                                 */
            /*                                                       */
            delta  = top + num_points;
            values = top;
            for ( nn = 0; nn < num_points; nn++ )
            {
              FT_Long  tmp = values[0];


              for ( mm = 1; mm < blend->num_designs; mm++ )
                tmp += FT_MulFix( *delta++, blend->weight_vector[mm] );

              *values++ = tmp;
            }

            known_othersubr_result_cnt = num_points;
            break;
          }

#ifdef CAN_HANDLE_NON_INTEGRAL_T1_OPERANDS

          /* We cannot yet enable these since currently  */
          /* our T1 stack stores integers which lack the */
          /* precision to express the values             */

        case 19:
          /* <idx> 1 19 callothersubr                             */
          /* => replace elements starting from index cvi( <idx> ) */
          /*    of BuildCharArray with WeightVector               */
          {
            FT_Int    idx;
            PS_Blend  blend = decoder->blend;


            if ( arg_cnt != 1 || blend == NULL )
              goto Unexpected_OtherSubr;

            idx = top[0];

            if ( idx < 0                                                 ||
                 idx + blend->num_designs > decoder->face->len_buildchar )
              goto Unexpected_OtherSubr;

            ft_memcpy( &decoder->buildchar[idx],
                       blend->weight_vector,
                       blend->num_designs *
                         sizeof( blend->weight_vector[0] ) );
          }
          break;

        case 20:
          /* <arg1> <arg2> 2 20 callothersubr pop   */
          /* ==> push <arg1> + <arg2> onto T1 stack */
          if ( arg_cnt != 2 )
            goto Unexpected_OtherSubr;

          top[0] += top[1]; /* XXX (over|under)flow */

          known_othersubr_result_cnt = 1;
          break;

        case 21:
          /* <arg1> <arg2> 2 21 callothersubr pop   */
          /* ==> push <arg1> - <arg2> onto T1 stack */
          if ( arg_cnt != 2 )
            goto Unexpected_OtherSubr;

          top[0] -= top[1]; /* XXX (over|under)flow */

          known_othersubr_result_cnt = 1;
          break;

        case 22:
          /* <arg1> <arg2> 2 22 callothersubr pop   */
          /* ==> push <arg1> * <arg2> onto T1 stack */
          if ( arg_cnt != 2 )
            goto Unexpected_OtherSubr;

          top[0] *= top[1]; /* XXX (over|under)flow */

          known_othersubr_result_cnt = 1;
          break;

        case 23:
          /* <arg1> <arg2> 2 23 callothersubr pop   */
          /* ==> push <arg1> / <arg2> onto T1 stack */
          if ( arg_cnt != 2 || top[1] == 0 )
            goto Unexpected_OtherSubr;

          top[0] /= top[1]; /* XXX (over|under)flow */

          known_othersubr_result_cnt = 1;
          break;

#endif /* CAN_HANDLE_NON_INTEGRAL_T1_OPERANDS */

        case 24:
          /* <val> <idx> 2 24 callothersubr              */
          /* => set BuildCharArray[cvi( <idx> )] = <val> */
          {
            FT_Int    idx;
            PS_Blend  blend = decoder->blend;

            if ( arg_cnt != 2 || blend == NULL )
              goto Unexpected_OtherSubr;

            idx = top[1];

            if ( idx < 0 || (FT_UInt) idx >= decoder->len_buildchar )
              goto Unexpected_OtherSubr;

            decoder->buildchar[idx] = top[0];
          }
          break;

        case 25:
          /* <idx> 1 25 callothersubr pop       */
          /* => push BuildCharArray[cvi( idx )] */
          /*    onto T1 stack                   */
          {
            FT_Int    idx;
            PS_Blend  blend = decoder->blend;

            if ( arg_cnt != 1 || blend == NULL )
              goto Unexpected_OtherSubr;

            idx = top[0];

            if ( idx < 0 || (FT_UInt) idx >= decoder->len_buildchar )
              goto Unexpected_OtherSubr;

            top[0] = decoder->buildchar[idx];
          }

          known_othersubr_result_cnt = 1;
          break;

#if 0
        case 26:
          /* <val> mark <idx> ==> set BuildCharArray[cvi( <idx> )] = <val>, */
          /*                      leave mark on T1 stack                    */
          /* <val> <idx>      ==> set BuildCharArray[cvi( <idx> )] = <val>  */
          XXX who has left his mark on the (PostScript) stack ?;
          break;
#endif

        case 27:
          /* <res1> <res2> <val1> <val2> 4 27 callothersubr pop */
          /* ==> push <res1> onto T1 stack if <val1> <= <val2>,  */
          /*     otherwise push <res2>                          */
          if ( arg_cnt != 4 )
            goto Unexpected_OtherSubr;

          if ( top[2] > top[3] )
            top[0] = top[1];

          known_othersubr_result_cnt = 1;
          break;

#ifdef CAN_HANDLE_NON_INTEGRAL_T1_OPERANDS
        case 28:
          /* 0 28 callothersubr pop                               */
          /* => push random value from interval [0, 1) onto stack */
          if ( arg_cnt != 0 )
            goto Unexpected_OtherSubr;

          top[0] = FT_rand();
          known_othersubr_result_cnt = 1;
          break;
#endif

        default:
          FT_ERROR(( "t1_decoder_parse_charstrings: "
                     "unknown othersubr [%d %d], wish me luck!\n",
                     arg_cnt, subr_no ));
          unknown_othersubr_result_cnt = arg_cnt;
          break;

        Unexpected_OtherSubr:
          FT_ERROR(( "t1_decoder_parse_charstrings: "
                     "invalid othersubr [%d %d]!\n", arg_cnt, subr_no ));
          goto Syntax_Error;
        }
