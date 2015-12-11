switch (do_background)
   {
      case PNG_BACKGROUND_GAMMA_SCREEN:
      case PNG_BACKGROUND_GAMMA_FILE:
      case PNG_BACKGROUND_GAMMA_UNIQUE:
         /* Standard PNG background processing. */
         if (alpha < 1)
         {
            if (alpha > 0)
            {
               input_sample = input_sample * alpha + background * (1-alpha);
               if (compose != NULL)
                  *compose = 1;
            }

            else
               input_sample = background;
         }
         break;

#ifdef PNG_READ_ALPHA_MODE_SUPPORTED
      case ALPHA_MODE_OFFSET + PNG_ALPHA_STANDARD:
      case ALPHA_MODE_OFFSET + PNG_ALPHA_BROKEN:
         /* The components are premultiplied in either case and the output is
          * gamma encoded (to get standard Porter-Duff we expect the output
          * gamma to be set to 1.0!)
          */
      case ALPHA_MODE_OFFSET + PNG_ALPHA_OPTIMIZED:
         /* The optimization is that the partial-alpha entries are linear
          * while the opaque pixels are gamma encoded, but this only affects the
          * output encoding.
          */
         if (alpha < 1)
         {
            if (alpha > 0)
            {
               input_sample *= alpha;
               if (compose != NULL)
                  *compose = 1;
            }

            else
               input_sample = 0;
         }
         break;
#endif

      default:
         /* Standard cases where no compositing is done (so the component
          * value is already correct.)
          */
         break;
   }
