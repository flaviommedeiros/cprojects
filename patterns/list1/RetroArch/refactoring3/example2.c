switch (id)
   {
#ifdef OLD_FFMPEG_API
      case CODEC_ID_MJPEG:
      case CODEC_ID_PNG:
#else
      case AV_CODEC_ID_MJPEG:
      case AV_CODEC_ID_PNG:
#endif
         return true;

      default:
         return false;
   }
