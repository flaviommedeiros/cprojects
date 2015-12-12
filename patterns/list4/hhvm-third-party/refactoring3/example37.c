switch (op->one_char)
      {
      case N_COLOUR:
      colour_option = (char *)"auto";
      break;

      case 'o':
      only_matching_last = add_number(0, only_matching_last);
      if (only_matching == NULL) only_matching = only_matching_last;
      break;

#ifdef JFRIEDL_DEBUG
      case 'S':
      S_arg = 0;
      break;
#endif
      }
