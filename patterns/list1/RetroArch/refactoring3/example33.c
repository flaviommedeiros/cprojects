switch (type)
   {
      case CORE_TYPE_PLAIN:
      case CORE_TYPE_DUMMY:
         cmd = persist ? EVENT_CMD_LOAD_CONTENT_PERSIST : EVENT_CMD_LOAD_CONTENT;
         break;
#ifdef HAVE_FFMPEG
      case CORE_TYPE_FFMPEG:
         cmd = EVENT_CMD_LOAD_CONTENT_FFMPEG;
         break;
#endif
      case CORE_TYPE_IMAGEVIEWER:
#ifdef HAVE_IMAGEVIEWER
         cmd = EVENT_CMD_LOAD_CONTENT_IMAGEVIEWER;
#endif
         break;
   }
