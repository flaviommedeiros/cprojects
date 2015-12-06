switch(view)
  {
#ifdef HAVE_GPHOTO2
    case DT_GUI_VIEW_SWITCH_TO_TETHERING:
      mode = DT_CAPTURE;
      break;
#endif

    case DT_GUI_VIEW_SWITCH_TO_DARKROOM:
      mode = DT_DEVELOP;
      break;

    case DT_GUI_VIEW_SWITCH_TO_LIBRARY:
      mode = DT_LIBRARY;
      break;

#ifdef HAVE_MAP
    case DT_GUI_VIEW_SWITCH_TO_MAP:
      mode = DT_MAP;
      break;
#endif
    case DT_GUI_VIEW_SWITCH_TO_SLIDESHOW:
      mode = DT_SLIDESHOW;
      break;
#ifdef HAVE_PRINT
    case DT_GUI_VIEW_SWITCH_TO_PRINT:
      mode = DT_PRINT;
      break;
#endif
  }
