switch ( filter )
    {
    case FT_LCD_FILTER_NONE:
      library->lcd_filter_func = NULL;
      library->lcd_extra       = 0;
      break;

    case FT_LCD_FILTER_DEFAULT:
#if defined( FT_FORCE_LEGACY_LCD_FILTER )

      library->lcd_filter_func = _ft_lcd_filter_legacy;
      library->lcd_extra       = 0;

#elif defined( FT_FORCE_LIGHT_LCD_FILTER )

      ft_memcpy( library->lcd_weights, light_filter, 5 );
      library->lcd_filter_func = _ft_lcd_filter_fir;
      library->lcd_extra       = 2;

#else

      ft_memcpy( library->lcd_weights, default_filter, 5 );
      library->lcd_filter_func = _ft_lcd_filter_fir;
      library->lcd_extra       = 2;

#endif

      break;

    case FT_LCD_FILTER_LIGHT:
      ft_memcpy( library->lcd_weights, light_filter, 5 );
      library->lcd_filter_func = _ft_lcd_filter_fir;
      library->lcd_extra       = 2;
      break;

#ifdef USE_LEGACY

    case FT_LCD_FILTER_LEGACY:
      library->lcd_filter_func = _ft_lcd_filter_legacy;
      library->lcd_extra       = 0;
      break;

#endif

    default:
      return FT_Err_Invalid_Argument;
    }
