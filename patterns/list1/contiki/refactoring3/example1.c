switch (k) {
#ifdef NCURSES_MOUSE_VERSION
  case KEY_MOUSE:
    {
      MEVENT event;

      if(getmouse(&event) == OK) {
        xpos = event.x;
        ypos = event.y;
        button = event.bstate & BUTTON1_PRESSED
          || event.bstate & BUTTON1_CLICKED
          || event.bstate & BUTTON1_DOUBLE_CLICKED;
        /*fprintf(stderr, "mevent: %d: %d, %d, %d, %lx ; %d\n",
           event.id, event.x, event.y, event.z, event.bstate, button); */
      }
      return;
    }
#endif
  case KEY_LEFT:
    key = CH_CURS_LEFT;
    break;
  case KEY_UP:
    key = CH_CURS_UP;
    break;
  case KEY_RIGHT:
    key = CH_CURS_RIGHT;
    break;
  case KEY_DOWN:
    key = CH_CURS_DOWN;
    break;
  case KEY_F(9):               /* Gnome uses F10 as menu trigger now... */
  case KEY_F(10):
    key = CTK_CONF_MENU_KEY;
    break;
  case '\r':
  case KEY_ENTER:
    key = CH_ENTER;
    break;
  case 127:
  case KEY_BACKSPACE:
  case KEY_DC:
    key = CH_DEL;
    break;
  case KEY_BTAB:
  case KEY_CTAB:
  case KEY_PPAGE:
  case KEY_PREVIOUS:
    key = CTK_CONF_WIDGETUP_KEY;
    break;
  case KEY_NPAGE:
  case KEY_NEXT:
    key = CTK_CONF_WIDGETDOWN_KEY;
    break;
  case KEY_STAB:
  case KEY_HOME:
  case KEY_END:
    key = CTK_CONF_WINDOWSWITCH_KEY;
    break;
  default:
    break;
  }
