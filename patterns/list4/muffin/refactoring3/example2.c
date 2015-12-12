switch (values[i].type)
        {
        case META_PROP_VALUE_INVALID:
          g_assert_not_reached ();
          break;
        case META_PROP_VALUE_UTF8_LIST:
          if (!utf8_list_from_results (&results,
                                       &values[i].v.string_list.strings,
                                       &values[i].v.string_list.n_strings))
            values[i].type = META_PROP_VALUE_INVALID;
          break;
        case META_PROP_VALUE_UTF8:
          if (!utf8_string_from_results (&results,
                                         &values[i].v.str))
            values[i].type = META_PROP_VALUE_INVALID;
          break;
        case META_PROP_VALUE_STRING:
          if (!latin1_string_from_results (&results,
                                           &values[i].v.str))
            values[i].type = META_PROP_VALUE_INVALID;
          break;
        case META_PROP_VALUE_STRING_AS_UTF8:
          if (!latin1_string_from_results (&results,
                                           &values[i].v.str))
            values[i].type = META_PROP_VALUE_INVALID;
          else
            {
              char *new_str;
              char *xmalloc_new_str;

              new_str = latin1_to_utf8 (values[i].v.str);
              xmalloc_new_str = ag_Xmalloc (strlen (new_str) + 1);
              if (xmalloc_new_str != NULL)
                {
                  strcpy (xmalloc_new_str, new_str);
                  meta_XFree (values[i].v.str);
                  values[i].v.str = xmalloc_new_str;
                }

              g_free (new_str);
            }
          break;
        case META_PROP_VALUE_MOTIF_HINTS:
          if (!motif_hints_from_results (&results,
                                         &values[i].v.motif_hints))
            values[i].type = META_PROP_VALUE_INVALID;
          break;
        case META_PROP_VALUE_CARDINAL_LIST:
          if (!cardinal_list_from_results (&results,
                                           &values[i].v.cardinal_list.cardinals,
                                           &values[i].v.cardinal_list.n_cardinals))
            values[i].type = META_PROP_VALUE_INVALID;
          break;
        case META_PROP_VALUE_CARDINAL:
          if (!cardinal_with_atom_type_from_results (&results,
                                                     values[i].required_type,
                                                     &values[i].v.cardinal))
            values[i].type = META_PROP_VALUE_INVALID;
          break;
        case META_PROP_VALUE_WINDOW:
          if (!window_from_results (&results,
                                    &values[i].v.xwindow))
            values[i].type = META_PROP_VALUE_INVALID;
          break;
        case META_PROP_VALUE_ATOM_LIST:
          if (!atom_list_from_results (&results,
                                       &values[i].v.atom_list.atoms,
                                       &values[i].v.atom_list.n_atoms))
            values[i].type = META_PROP_VALUE_INVALID;
          break;
        case META_PROP_VALUE_TEXT_PROPERTY:
          if (!text_property_from_results (&results, &values[i].v.str))
            values[i].type = META_PROP_VALUE_INVALID;
          break;
        case META_PROP_VALUE_WM_HINTS:
          if (!wm_hints_from_results (&results, &values[i].v.wm_hints))
            values[i].type = META_PROP_VALUE_INVALID;
          break;
        case META_PROP_VALUE_CLASS_HINT:
          if (!class_hint_from_results (&results, &values[i].v.class_hint))
            values[i].type = META_PROP_VALUE_INVALID;
          break;
        case META_PROP_VALUE_SIZE_HINTS:
          if (!size_hints_from_results (&results,
                                        &values[i].v.size_hints.hints,
                                        &values[i].v.size_hints.flags))
            values[i].type = META_PROP_VALUE_INVALID;
          break;
#ifdef HAVE_XSYNC
        case META_PROP_VALUE_SYNC_COUNTER:
          if (!counter_from_results (&results,
                                     &values[i].v.xcounter))
            values[i].type = META_PROP_VALUE_INVALID;
          break;
        case META_PROP_VALUE_SYNC_COUNTER_LIST:
          if (!counter_list_from_results (&results,
                                          &values[i].v.xcounter_list.counters,
                                          &values[i].v.xcounter_list.n_counters))
            values[i].type = META_PROP_VALUE_INVALID;
          break;
#else
        case META_PROP_VALUE_SYNC_COUNTER:
        case META_PROP_VALUE_SYNC_COUNTER_LIST:
          values[i].type = META_PROP_VALUE_INVALID;
          if (results.prop)
            {
              XFree (results.prop);
              results.prop = NULL;
            }
          break;
#endif
        }
