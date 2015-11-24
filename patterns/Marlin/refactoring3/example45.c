switch(msg)
  {
    default:
    /*
    case U8G_DEV_MSG_INIT:
    case U8G_DEV_MSG_STOP:
    case U8G_DEV_MSG_PAGE_FIRST:
    case U8G_DEV_MSG_PAGE_NEXT:
    case U8G_DEV_MSG_SET_COLOR_INDEX:
    case U8G_DEV_MSG_SET_XY_CB:
    */
      return u8g_call_dev_fn(u8g, rotation_chain, msg, arg);
#ifdef U8G_DEV_MSG_IS_BBX_INTERSECTION
    case U8G_DEV_MSG_IS_BBX_INTERSECTION:
      {
        u8g_dev_arg_bbx_t *bbx = (u8g_dev_arg_bbx_t *)arg;
        u8g_uint_t x, y, tmp;
        
        /* transform the reference point */
        y = bbx->x;
        x = u8g->height;
        /* x = u8g_GetWidthLL(u8g, rotation_chain); */
        x -= bbx->y; 
        x--;
        
        /* adjust point to be the uppler left corner again */
        x -= bbx->h;
        x++;
        
        /* swap box dimensions */        
        tmp = bbx->w;
        bbx->w = bbx->h;
        bbx->h = tmp;
        
        /* store x,y */
        bbx->x = x;
        bbx->y = y;
      }
      return u8g_call_dev_fn(u8g, rotation_chain, msg, arg);
#endif /* U8G_DEV_MSG_IS_BBX_INTERSECTION */
    case U8G_DEV_MSG_GET_PAGE_BOX:
      /* get page size from next device in the chain */
      u8g_call_dev_fn(u8g, rotation_chain, msg, arg);
      //printf("pre x: %3d..%3d y: %3d..%3d   ", ((u8g_box_t *)arg)->x0, ((u8g_box_t *)arg)->x1, ((u8g_box_t *)arg)->y0, ((u8g_box_t *)arg)->y1);
      {
	u8g_box_t new_box;
	//new_box.x0 = u8g_GetHeightLL(u8g,rotation_chain) - ((u8g_box_t *)arg)->y1 - 1;
	//new_box.x1 = u8g_GetHeightLL(u8g,rotation_chain) - ((u8g_box_t *)arg)->y0 - 1;
	
	new_box.x0 = ((u8g_box_t *)arg)->y0;
	new_box.x1 = ((u8g_box_t *)arg)->y1;
	new_box.y0 = ((u8g_box_t *)arg)->x0;
	new_box.y1 = ((u8g_box_t *)arg)->x1;
	*((u8g_box_t *)arg) = new_box;
	//printf("post x: %3d..%3d y: %3d..%3d\n", ((u8g_box_t *)arg)->x0, ((u8g_box_t *)arg)->x1, ((u8g_box_t *)arg)->y0, ((u8g_box_t *)arg)->y1);
      }
      break;
    case U8G_DEV_MSG_GET_WIDTH:
      *((u8g_uint_t *)arg) = u8g_GetHeightLL(u8g,rotation_chain);
      break;
    case U8G_DEV_MSG_GET_HEIGHT:
      *((u8g_uint_t *)arg) = u8g_GetWidthLL(u8g, rotation_chain);
      break;
    case U8G_DEV_MSG_SET_PIXEL:
      {
        u8g_uint_t x, y;
        y = ((u8g_dev_arg_pixel_t *)arg)->x;
        x = u8g_GetWidthLL(u8g, rotation_chain);
        x -= ((u8g_dev_arg_pixel_t *)arg)->y; 
        x--;
        ((u8g_dev_arg_pixel_t *)arg)->x = x;
        ((u8g_dev_arg_pixel_t *)arg)->y = y;
      }
      u8g_call_dev_fn(u8g, rotation_chain, msg, arg);
      break;
    case U8G_DEV_MSG_SET_8PIXEL:
      {
        u8g_uint_t x, y;
	//uint16_t x,y;
        y = ((u8g_dev_arg_pixel_t *)arg)->x;
        x = u8g_GetWidthLL(u8g, rotation_chain);
        x -= ((u8g_dev_arg_pixel_t *)arg)->y; 
        x--;
        ((u8g_dev_arg_pixel_t *)arg)->x = x;
        ((u8g_dev_arg_pixel_t *)arg)->y = y;
        ((u8g_dev_arg_pixel_t *)arg)->dir+=1;
        ((u8g_dev_arg_pixel_t *)arg)->dir &= 3;
      }
      u8g_call_dev_fn(u8g, rotation_chain, msg, arg);
      break;
  }
