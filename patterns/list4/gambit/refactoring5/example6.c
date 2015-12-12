#ifdef USE_CURSES
if (lineeditor_cap (d, LINEEDITOR_CAP_CLEAR) != NULL)
        e = lineeditor_output_cap0 (d, LINEEDITOR_CAP_CLEAR, 1);
      else

#endif

        e = lineeditor_left_margin_of_next_row (d);
