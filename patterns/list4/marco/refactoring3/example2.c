switch (peek_state (info))
    {
    case STATE_START:
      break;
    case STATE_THEME:
      g_assert (info->theme);

      if (!meta_theme_validate (info->theme, error))
        {
          add_context_to_error (error, context);
          meta_theme_free (info->theme);
          info->theme = NULL;
        }

      pop_state (info);
      g_assert (peek_state (info) == STATE_START);
      break;
    case STATE_INFO:
      pop_state (info);
      g_assert (peek_state (info) == STATE_THEME);
      break;
    case STATE_NAME:
      pop_state (info);
      g_assert (peek_state (info) == STATE_INFO);
      break;
    case STATE_AUTHOR:
      pop_state (info);
      g_assert (peek_state (info) == STATE_INFO);
      break;
    case STATE_COPYRIGHT:
      pop_state (info);
      g_assert (peek_state (info) == STATE_INFO);
      break;
    case STATE_DATE:
      pop_state (info);
      g_assert (peek_state (info) == STATE_INFO);
      break;
    case STATE_DESCRIPTION:
      pop_state (info);
      g_assert (peek_state (info) == STATE_INFO);
      break;
    case STATE_CONSTANT:
      pop_state (info);
      g_assert (peek_state (info) == STATE_THEME);
      break;
    case STATE_FRAME_GEOMETRY:
      g_assert (info->layout);

      if (!meta_frame_layout_validate (info->layout,
                                       error))
        {
          add_context_to_error (error, context);
        }

      /* layout will already be stored in the theme under
       * its name
       */
      meta_frame_layout_unref (info->layout);
      info->layout = NULL;
      pop_state (info);
      g_assert (peek_state (info) == STATE_THEME);
      break;
    case STATE_DISTANCE:
      pop_state (info);
      g_assert (peek_state (info) == STATE_FRAME_GEOMETRY);
      break;
    case STATE_BORDER:
      pop_state (info);
      g_assert (peek_state (info) == STATE_FRAME_GEOMETRY);
      break;
    case STATE_ASPECT_RATIO:
      pop_state (info);
      g_assert (peek_state (info) == STATE_FRAME_GEOMETRY);
      break;
    case STATE_DRAW_OPS:
      {
        g_assert (info->op_list);

        if (!meta_draw_op_list_validate (info->op_list,
                                         error))
          {
            add_context_to_error (error, context);
            meta_draw_op_list_unref (info->op_list);
            info->op_list = NULL;
          }

        pop_state (info);

        switch (peek_state (info))
          {
          case STATE_BUTTON:
          case STATE_PIECE:
          case STATE_MENU_ICON:
            /* Leave info->op_list to be picked up
             * when these elements are closed
             */
            g_assert (info->op_list);
            break;
          case STATE_THEME:
            g_assert (info->op_list);
            meta_draw_op_list_unref (info->op_list);
            info->op_list = NULL;
            break;
          default:
            /* Op list can't occur in other contexts */
            g_assert_not_reached ();
            break;
          }
      }
      break;
    case STATE_LINE:
      pop_state (info);
      g_assert (peek_state (info) == STATE_DRAW_OPS);
      break;
    case STATE_RECTANGLE:
      pop_state (info);
      g_assert (peek_state (info) == STATE_DRAW_OPS);
      break;
    case STATE_ARC:
      pop_state (info);
      g_assert (peek_state (info) == STATE_DRAW_OPS);
      break;
    case STATE_CLIP:
      pop_state (info);
      g_assert (peek_state (info) == STATE_DRAW_OPS);
      break;
    case STATE_TINT:
      pop_state (info);
      g_assert (peek_state (info) == STATE_DRAW_OPS);
      break;
    case STATE_GRADIENT:
      g_assert (info->op);
      g_assert (info->op->type == META_DRAW_GRADIENT);
      if (!meta_gradient_spec_validate (info->op->data.gradient.gradient_spec,
                                        error))
        {
          add_context_to_error (error, context);
          meta_draw_op_free (info->op);
          info->op = NULL;
        }
      else
        {
          g_assert (info->op_list);
          meta_draw_op_list_append (info->op_list, info->op);
          info->op = NULL;
        }
      pop_state (info);
      g_assert (peek_state (info) == STATE_DRAW_OPS);
      break;
    case STATE_IMAGE:
      pop_state (info);
      g_assert (peek_state (info) == STATE_DRAW_OPS);
      break;
    case STATE_GTK_ARROW:
      pop_state (info);
      g_assert (peek_state (info) == STATE_DRAW_OPS);
      break;
    case STATE_GTK_BOX:
      pop_state (info);
      g_assert (peek_state (info) == STATE_DRAW_OPS);
      break;
    case STATE_GTK_VLINE:
      pop_state (info);
      g_assert (peek_state (info) == STATE_DRAW_OPS);
      break;
    case STATE_ICON:
      pop_state (info);
      g_assert (peek_state (info) == STATE_DRAW_OPS);
      break;
    case STATE_TITLE:
      pop_state (info);
      g_assert (peek_state (info) == STATE_DRAW_OPS);
      break;
    case STATE_INCLUDE:
      pop_state (info);
      g_assert (peek_state (info) == STATE_DRAW_OPS);
      break;
    case STATE_TILE:
      pop_state (info);
      g_assert (peek_state (info) == STATE_DRAW_OPS);
      break;
    case STATE_COLOR:
      pop_state (info);
      g_assert (peek_state (info) == STATE_GRADIENT);
      break;
    case STATE_FRAME_STYLE:
      g_assert (info->style);

      if (!meta_frame_style_validate (info->style,
                                      info->theme->format_version,
                                      error))
        {
          add_context_to_error (error, context);
        }

      /* Frame style is in the theme hash table and a ref
       * is held there
       */
      meta_frame_style_unref (info->style);
      info->style = NULL;
      pop_state (info);
      g_assert (peek_state (info) == STATE_THEME);
      break;
    case STATE_PIECE:
      g_assert (info->style);
      if (info->op_list == NULL)
        {
          set_error (error, context, G_MARKUP_ERROR, G_MARKUP_ERROR_PARSE,
                     _("No draw_ops provided for frame piece"));
        }
      else
        {
          info->style->pieces[info->piece] = info->op_list;
          info->op_list = NULL;
        }
      pop_state (info);
      g_assert (peek_state (info) == STATE_FRAME_STYLE);
      break;
    case STATE_BUTTON:
      g_assert (info->style);
      if (info->op_list == NULL)
        {
          set_error (error, context, G_MARKUP_ERROR, G_MARKUP_ERROR_PARSE,
                     _("No draw_ops provided for button"));
        }
      else
        {
          info->style->buttons[info->button_type][info->button_state] =
            info->op_list;
          info->op_list = NULL;
        }
      pop_state (info);
      break;
#ifdef USE_UBUNTU_CODE
    case STATE_SHADOW:
      g_assert (info->style);
      pop_state (info);
      break;
    case STATE_PADDING:
      g_assert (info->style);
      pop_state (info);
      break;
#endif
    case STATE_MENU_ICON:
      g_assert (info->theme);
      if (info->op_list != NULL)
        {
          meta_draw_op_list_unref (info->op_list);
          info->op_list = NULL;
        }
      pop_state (info);
      g_assert (peek_state (info) == STATE_THEME);
      break;
    case STATE_FRAME_STYLE_SET:
      g_assert (info->style_set);

      if (!meta_frame_style_set_validate (info->style_set,
                                          error))
        {
          add_context_to_error (error, context);
        }

      /* Style set is in the theme hash table and a reference
       * is held there.
       */
      meta_frame_style_set_unref (info->style_set);
      info->style_set = NULL;
      pop_state (info);
      g_assert (peek_state (info) == STATE_THEME);
      break;
    case STATE_FRAME:
      pop_state (info);
      g_assert (peek_state (info) == STATE_FRAME_STYLE_SET);
      break;
    case STATE_WINDOW:
      pop_state (info);
      g_assert (peek_state (info) == STATE_THEME);
      break;
    case STATE_FALLBACK:
      pop_state (info);
      g_assert (peek_state (info) == STATE_THEME);
      break;
    }
