switch(msg)
  {
    case U8G_DEV_MSG_SET_8PIXEL:                /* most often used command */
      break;
    case U8G_DEV_MSG_SET_PIXEL:
      break;
    case U8G_DEV_MSG_INIT:
      break;
    case U8G_DEV_MSG_STOP:
      break;
    case U8G_DEV_MSG_PAGE_FIRST:
      break;
    case U8G_DEV_MSG_PAGE_NEXT:
      break;
#ifdef U8G_DEV_MSG_IS_BBX_INTERSECTION
    case U8G_DEV_MSG_IS_BBX_INTERSECTION:
      return 1;
#endif
    case U8G_DEV_MSG_GET_PAGE_BOX:
      break;
    case U8G_DEV_MSG_SET_COLOR_INDEX:
      break;
    case U8G_DEV_MSG_SET_XY_CB:
      break;
  }
