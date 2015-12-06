#  ifdef PNG_CHECK_cHRM_SUPPORTED
if (png_check_cHRM_fixed(png_ptr,
       white_x, white_y, red_x, red_y, green_x, green_y, blue_x, blue_y))
#  endif
   {
      info_ptr->x_white = white_x;
      info_ptr->y_white = white_y;
      info_ptr->x_red   = red_x;
      info_ptr->y_red   = red_y;
      info_ptr->x_green = green_x;
      info_ptr->y_green = green_y;
      info_ptr->x_blue  = blue_x;
      info_ptr->y_blue  = blue_y;
      info_ptr->valid |= PNG_INFO_cHRM;
   }
