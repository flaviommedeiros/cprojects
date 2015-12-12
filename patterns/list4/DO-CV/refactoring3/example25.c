switch ((pp->options >> PNG_ARM_NEON) & 3)
   {
      case PNG_OPTION_UNSET:
         /* Allow the run-time check to execute if it has been enabled -
          * thus both API and CHECK can be turned on.  If it isn't supported
          * this case will fall through to the 'default' below, which just
          * returns.
          */
#endif /* PNG_ARM_NEON_API_SUPPORTED */
#ifdef PNG_ARM_NEON_CHECK_SUPPORTED
         {
            static volatile sig_atomic_t no_neon = -1; /* not checked */

            if (no_neon < 0)
               no_neon = !png_have_neon(pp);

            if (no_neon)
               return;
         }
#ifdef PNG_ARM_NEON_API_SUPPORTED
         break;
#endif
#endif /* PNG_ARM_NEON_CHECK_SUPPORTED */
#ifdef PNG_ARM_NEON_API_SUPPORTED
      case PNG_OPTION_ON:
         /* Option turned on */
         break;

      default: /* OFF or INVALID */
         return;
   }
