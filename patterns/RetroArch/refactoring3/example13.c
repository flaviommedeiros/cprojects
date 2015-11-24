switch (rarch_path_is_media_type(fullpath))
         {
            case RARCH_CONTENT_MOVIE:
            case RARCH_CONTENT_MUSIC:
               if (settings->multimedia.builtin_mediaplayer_enable)
               {
#ifdef HAVE_FFMPEG
                  global->has_set.libretro              = false;
                  global->inited.core.type              = CORE_TYPE_FFMPEG;
#endif
               }
               break;
#ifdef HAVE_IMAGEVIEWER
            case RARCH_CONTENT_IMAGE:
               if (settings->multimedia.builtin_imageviewer_enable)
               {
                  global->has_set.libretro              = false;
                  global->inited.core.type              = CORE_TYPE_IMAGEVIEWER;
               }
               break;
#endif
            default:
               break;
         }
