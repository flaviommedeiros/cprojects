#ifdef PNG_CHECK_cHRM_SUPPORTED
if (png_check_cHRM_fixed(png_ptr,
      white_x, white_y, red_x, red_y, green_x, green_y, blue_x, blue_y))
#endif
   {
      info_ptr->int_x_white = white_x;
      info_ptr->int_y_white = white_y;
      info_ptr->int_x_red   = red_x;
      info_ptr->int_y_red   = red_y;
      info_ptr->int_x_green = green_x;
      info_ptr->int_y_green = green_y;
      info_ptr->int_x_blue  = blue_x;
      info_ptr->int_y_blue  = blue_y;
#ifdef  PNG_FLOATING_POINT_SUPPORTED
      info_ptr->x_white = (float)(white_x/100000.);
      info_ptr->y_white = (float)(white_y/100000.);
      info_ptr->x_red   = (float)(  red_x/100000.);
      info_ptr->y_red   = (float)(  red_y/100000.);
      info_ptr->x_green = (float)(green_x/100000.);
      info_ptr->y_green = (float)(green_y/100000.);
      info_ptr->x_blue  = (float)( blue_x/100000.);
      info_ptr->y_blue  = (float)( blue_y/100000.);
#endif
      info_ptr->valid |= PNG_INFO_cHRM;
   }
