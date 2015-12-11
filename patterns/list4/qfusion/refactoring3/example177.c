switch (do_background)
            {
            case PNG_BACKGROUND_GAMMA_SCREEN:
            case PNG_BACKGROUND_GAMMA_FILE:
            case PNG_BACKGROUND_GAMMA_UNIQUE:
               use_background = (alpha >= 0 && alpha < 1);
               /*FALL THROUGH*/
#           ifdef PNG_READ_ALPHA_MODE_SUPPORTED
               case ALPHA_MODE_OFFSET + PNG_ALPHA_STANDARD:
               case ALPHA_MODE_OFFSET + PNG_ALPHA_BROKEN:
               case ALPHA_MODE_OFFSET + PNG_ALPHA_OPTIMIZED:
#           endif /* ALPHA_MODE_SUPPORTED */
               do_compose = (alpha > 0 && alpha < 1);
               use_input = (alpha != 0);
               break;

            default:
               break;
            }
