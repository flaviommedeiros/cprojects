switch (peek_state (info))
    {
    case STATE_START:
      g_assert_not_reached (); /* gmarkup shouldn't do this */
      break;
    case STATE_THEME:
      NO_TEXT ("metacity_theme");
      break;
    case STATE_INFO:
      NO_TEXT ("info");
      break;
    case STATE_NAME:
      if (info->theme->readable_name != NULL)
        {
          set_error (error, context, G_MARKUP_ERROR,
                     G_MARKUP_ERROR_PARSE,
                     _("<%s> specified twice for this theme"),
                     "name");
          return;
        }

      info->theme->readable_name = g_strndup (text, text_len);
      break;
    case STATE_AUTHOR:
      if (info->theme->author != NULL)
        {
          set_error (error, context, G_MARKUP_ERROR,
                     G_MARKUP_ERROR_PARSE,
                     _("<%s> specified twice for this theme"),
                     "author");
          return;
        }

      info->theme->author = g_strndup (text, text_len);
      break;
    case STATE_COPYRIGHT:
      if (info->theme->copyright != NULL)
        {
          set_error (error, context, G_MARKUP_ERROR,
                     G_MARKUP_ERROR_PARSE,
                     _("<%s> specified twice for this theme"),
                     "copyright");
          return;
        }

      info->theme->copyright = g_strndup (text, text_len);
      break;
    case STATE_DATE:
      if (info->theme->date != NULL)
        {
          set_error (error, context, G_MARKUP_ERROR,
                     G_MARKUP_ERROR_PARSE,
                     _("<%s> specified twice for this theme"),
                     "date");
          return;
        }

      info->theme->date = g_strndup (text, text_len);
      break;
    case STATE_DESCRIPTION:
      if (info->theme->description != NULL)
        {
          set_error (error, context, G_MARKUP_ERROR,
                     G_MARKUP_ERROR_PARSE,
                     _("<%s> specified twice for this theme"),
                     "description");
          return;
        }

      info->theme->description = g_strndup (text, text_len);
      break;
    case STATE_CONSTANT:
      NO_TEXT ("constant");
      break;
    case STATE_FRAME_GEOMETRY:
      NO_TEXT ("frame_geometry");
      break;
    case STATE_DISTANCE:
      NO_TEXT ("distance");
      break;
    case STATE_BORDER:
      NO_TEXT ("border");
      break;
    case STATE_ASPECT_RATIO:
      NO_TEXT ("aspect_ratio");
      break;
    case STATE_DRAW_OPS:
      NO_TEXT ("draw_ops");
      break;
    case STATE_LINE:
      NO_TEXT ("line");
      break;
    case STATE_RECTANGLE:
      NO_TEXT ("rectangle");
      break;
    case STATE_ARC:
      NO_TEXT ("arc");
      break;
    case STATE_CLIP:
      NO_TEXT ("clip");
      break;
    case STATE_TINT:
      NO_TEXT ("tint");
      break;
    case STATE_GRADIENT:
      NO_TEXT ("gradient");
      break;
    case STATE_IMAGE:
      NO_TEXT ("image");
      break;
    case STATE_GTK_ARROW:
      NO_TEXT ("gtk_arrow");
      break;
    case STATE_GTK_BOX:
      NO_TEXT ("gtk_box");
      break;
    case STATE_GTK_VLINE:
      NO_TEXT ("gtk_vline");
      break;
    case STATE_ICON:
      NO_TEXT ("icon");
      break;
    case STATE_TITLE:
      NO_TEXT ("title");
      break;
    case STATE_INCLUDE:
      NO_TEXT ("include");
      break;
    case STATE_TILE:
      NO_TEXT ("tile");
      break;
    case STATE_COLOR:
      NO_TEXT ("color");
      break;
    case STATE_FRAME_STYLE:
      NO_TEXT ("frame_style");
      break;
    case STATE_PIECE:
      NO_TEXT ("piece");
      break;
    case STATE_BUTTON:
      NO_TEXT ("button");
      break;
#ifdef USE_UBUNTU_CODE
    case STATE_SHADOW:
      NO_TEXT ("shadow");
      break;
    case STATE_PADDING:
      NO_TEXT ("padding");
      break;
#endif
    case STATE_MENU_ICON:
      NO_TEXT ("menu_icon");
      break;
    case STATE_FRAME_STYLE_SET:
      NO_TEXT ("frame_style_set");
      break;
    case STATE_FRAME:
      NO_TEXT ("frame");
      break;
    case STATE_WINDOW:
      NO_TEXT ("window");
      break;
    case STATE_FALLBACK:
      NO_TEXT ("fallback");
      break;
    }
