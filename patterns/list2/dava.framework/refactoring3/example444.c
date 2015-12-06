switch (Type)
	{
#ifndef IL_NO_JPG
		case MP3_JPG:
			return iLoadJpegInternal();
#endif//IL_NO_JPG

#ifndef IL_NO_PNG
		case MP3_PNG:
			return iLoadPngInternal();
#endif//IL_NO_PNG

		// Either a picture was not found, or the MIME type was not recognized.
		default:
			ilSetError(IL_INVALID_FILE_HEADER);
	}
