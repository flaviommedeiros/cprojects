switch (id)
   {
#ifdef OLD_FFMPEG_API
      case CODEC_ID_SSA:
#else
      case AV_CODEC_ID_ASS:
      case AV_CODEC_ID_SSA:
#endif
         return true;
      default:
         return false;
   }
