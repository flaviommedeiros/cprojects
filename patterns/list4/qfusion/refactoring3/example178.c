switch (do_background)
   {
      default:
         base = "";
         bg = 4; /* should not be used */
         break;
      case PNG_BACKGROUND_GAMMA_SCREEN:
         base = " bckg(Screen):";
         bg = 1/screen_gamma;
         break;
      case PNG_BACKGROUND_GAMMA_FILE:
         base = " bckg(File):";
         bg = file_gamma;
         break;
      case PNG_BACKGROUND_GAMMA_UNIQUE:
         base = " bckg(Unique):";
         /* This tests the handling of a unique value, the math is such that the
          * value tends to be <1, but is neither screen nor file (even if they
          * match!)
          */
         bg = (file_gamma + screen_gamma) / 3;
         break;
#ifdef PNG_READ_ALPHA_MODE_SUPPORTED
      case ALPHA_MODE_OFFSET + PNG_ALPHA_PNG:
         base = " alpha(PNG)";
         bg = 4; /* should not be used */
         break;
      case ALPHA_MODE_OFFSET + PNG_ALPHA_STANDARD:
         base = " alpha(Porter-Duff)";
         bg = 4; /* should not be used */
         break;
      case ALPHA_MODE_OFFSET + PNG_ALPHA_OPTIMIZED:
         base = " alpha(Optimized)";
         bg = 4; /* should not be used */
         break;
      case ALPHA_MODE_OFFSET + PNG_ALPHA_BROKEN:
         base = " alpha(Broken)";
         bg = 4; /* should not be used */
         break;
#endif
   }
