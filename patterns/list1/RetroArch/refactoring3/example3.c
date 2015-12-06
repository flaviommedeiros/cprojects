switch (id)
   {
#ifdef OLD_FFMPEG_API
      case CODEC_ID_TTF:
#else
      case AV_CODEC_ID_TTF:
#endif
         return true;

      default:
       return false;
   }
