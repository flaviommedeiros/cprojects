switch (pad_type[pad])
   {
#ifdef HW_RVL
      case WPAD_EXP_NONE:
         return "Wiimote Controller";
      case WPAD_EXP_NUNCHUK:
         return "Nunchuk Controller";
      case WPAD_EXP_CLASSIC:
         return "Classic Controller";
#ifdef HAVE_LIBSICKSAXIS
      case WPAD_EXP_SICKSAXIS:
         return "Sixaxis Controller";
#endif
#endif
      case WPAD_EXP_GAMECUBE:
         return "GameCube Controller";
   }
