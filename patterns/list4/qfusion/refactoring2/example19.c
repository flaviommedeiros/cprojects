#ifdef PNG_READ_ALPHA_MODE_SUPPORTED
if (do_background != ALPHA_MODE_OFFSET + PNG_ALPHA_BROKEN)
#endif
         {
            /* In all other cases the output alpha channel is linear already,
             * don't log errors here, they are much larger in linear data.
             */
            output_is_encoded = 0;
            log_max_error = 0;
         }
