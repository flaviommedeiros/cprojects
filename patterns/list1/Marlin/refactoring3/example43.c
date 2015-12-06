switch(msg)
  {
    case U8G_DEV_MSG_INIT:
      break;
    case U8G_DEV_MSG_STOP:
      break;
    case U8G_DEV_MSG_PAGE_FIRST:
      u8g_pb_Clear(pb);
      u8g_page_First(&(pb->p));
      break;
    case U8G_DEV_MSG_PAGE_NEXT:
      /*
      {
        uint8_t i, j;
        uint8_t page_height;
        page_height = pb->p.page_y1;
        page_height -= pb->p.page_y0;
        page_height++;
        for( j = 0; j < page_height; j++ )
        {
          printf("%02d ", j);
          for( i = 0; i < WIDTH; i++ )
          {
            if ( (u8g_pb_dev_stdout_buf[i] & (1<<j)) != 0 )
              printf("#");
            else
              printf(".");
          }
          printf("\n");
        }
      }
      */
      if ( u8g_page_Next(&(pb->p)) == 0 )
      {
        //printf("\n");
        return 0;
      }
      u8g_pb_Clear(pb);
      break;
#ifdef U8G_DEV_MSG_IS_BBX_INTERSECTION
    case U8G_DEV_MSG_IS_BBX_INTERSECTION:
       {
        u8g_dev_arg_bbx_t *bbx = (u8g_dev_arg_bbx_t *)arg;
        u8g_uint_t x2, y2;

        y2 = bbx->y;
        y2 += bbx->h;
        y2--;
        
        if ( u8g_pb_IsYIntersection(pb, bbx->y, y2) == 0 )
          return 0;
        
        /* maybe this one can be skiped... probability is very high to have an intersection, so it would be ok to always return 1 */
        x2 = bbx->x;
        x2 += bbx->w;
        x2--;
        
        if ( u8g_pb_IsXIntersection(pb, bbx->x, x2) == 0 )
          return 0;
      }
      return 1;
#endif
    case U8G_DEV_MSG_GET_PAGE_BOX:
      u8g_pb_GetPageBox(pb, (u8g_box_t *)arg);
      break;
    case U8G_DEV_MSG_SET_COLOR_INDEX:
      break;
    case U8G_DEV_MSG_SET_XY_CB:
      break;
  }
