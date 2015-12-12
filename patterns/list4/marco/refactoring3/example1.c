switch (peek_state (info))
    {
    case STATE_START:
      if (strcmp (element_name, "metacity_theme") == 0)
        {
          info->theme = meta_theme_new ();
          info->theme->name = g_strdup (info->theme_name);
          info->theme->filename = g_strdup (info->theme_file);
          info->theme->dirname = g_strdup (info->theme_dir);
          info->theme->format_version = info->format_version;

          push_state (info, STATE_THEME);
        }
      else
        set_error (error, context, G_MARKUP_ERROR, G_MARKUP_ERROR_PARSE,
                   _("Outermost element in theme must be <metacity_theme> not <%s>"),
                   element_name);
      break;

    case STATE_THEME:
      parse_toplevel_element (context, element_name,
                              attribute_names, attribute_values,
                              info, error);
      break;
    case STATE_INFO:
      parse_info_element (context, element_name,
                          attribute_names, attribute_values,
                          info, error);
      break;
    case STATE_NAME:
    case STATE_AUTHOR:
    case STATE_COPYRIGHT:
    case STATE_DATE:
    case STATE_DESCRIPTION:
      set_error (error, context, G_MARKUP_ERROR, G_MARKUP_ERROR_PARSE,
                 _("Element <%s> is not allowed inside a name/author/date/description element"),
                 element_name);
      break;
    case STATE_CONSTANT:
      set_error (error, context, G_MARKUP_ERROR, G_MARKUP_ERROR_PARSE,
                 _("Element <%s> is not allowed inside a <constant> element"),
                 element_name);
      break;
    case STATE_FRAME_GEOMETRY:
      parse_geometry_element (context, element_name,
                              attribute_names, attribute_values,
                              info, error);
      break;
    case STATE_DISTANCE:
    case STATE_BORDER:
    case STATE_ASPECT_RATIO:
      set_error (error, context, G_MARKUP_ERROR, G_MARKUP_ERROR_PARSE,
                 _("Element <%s> is not allowed inside a distance/border/aspect_ratio element"),
                 element_name);
      break;
    case STATE_DRAW_OPS:
      parse_draw_op_element (context, element_name,
                             attribute_names, attribute_values,
                             info, error);
      break;
    case STATE_LINE:
    case STATE_RECTANGLE:
    case STATE_ARC:
    case STATE_CLIP:
    case STATE_TINT:
    case STATE_IMAGE:
    case STATE_GTK_ARROW:
    case STATE_GTK_BOX:
    case STATE_GTK_VLINE:
    case STATE_ICON:
    case STATE_TITLE:
    case STATE_INCLUDE:
    case STATE_TILE:
      set_error (error, context, G_MARKUP_ERROR, G_MARKUP_ERROR_PARSE,
                 _("Element <%s> is not allowed inside a draw operation element"),
                 element_name);
      break;
    case STATE_GRADIENT:
      parse_gradient_element (context, element_name,
                              attribute_names, attribute_values,
                              info, error);
      break;
    case STATE_COLOR:
      set_error (error, context, G_MARKUP_ERROR, G_MARKUP_ERROR_PARSE,
                 _("Element <%s> is not allowed inside a <%s> element"),
                 element_name, "color");
      break;
    case STATE_FRAME_STYLE:
      parse_style_element (context, element_name,
                           attribute_names, attribute_values,
                           info, error);
      break;
    case STATE_PIECE:
      parse_piece_element (context, element_name,
                           attribute_names, attribute_values,
                           info, error);
      break;
    case STATE_BUTTON:
      parse_button_element (context, element_name,
                            attribute_names, attribute_values,
                            info, error);
      break;
#ifdef USE_UBUNTU_CODE
    case STATE_SHADOW:
       parse_shadow_element (context, element_name,
                             attribute_names, attribute_values,
                             info, error);
       break;
    case STATE_PADDING:
       parse_padding_element (context, element_name,
                              attribute_names, attribute_values,
                              info, error);
       break;
#endif
    case STATE_MENU_ICON:
      parse_menu_icon_element (context, element_name,
                               attribute_names, attribute_values,
                               info, error);
      break;
    case STATE_FRAME_STYLE_SET:
      parse_style_set_element (context, element_name,
                               attribute_names, attribute_values,
                               info, error);
      break;
    case STATE_FRAME:
      set_error (error, context, G_MARKUP_ERROR, G_MARKUP_ERROR_PARSE,
                 _("Element <%s> is not allowed inside a <%s> element"),
                 element_name, "frame");
      break;
    case STATE_WINDOW:
      set_error (error, context, G_MARKUP_ERROR, G_MARKUP_ERROR_PARSE,
                 _("Element <%s> is not allowed inside a <%s> element"),
                 element_name, "window");
      break;
    case STATE_FALLBACK:
      set_error (error, context, G_MARKUP_ERROR, G_MARKUP_ERROR_PARSE,
                 _("Element <%s> is not allowed inside a <%s> element"),
                 element_name, "fallback");
      break;
    }
