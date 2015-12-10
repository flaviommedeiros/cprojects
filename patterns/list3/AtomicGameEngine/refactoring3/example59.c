switch (pixel_format) {
    case SDL_PIXELFORMAT_ARGB8888:
        *internalFormat = GL_RGBA8;
        *format = GL_BGRA;
        *type = GL_UNSIGNED_INT_8_8_8_8_REV;
        break;
    case SDL_PIXELFORMAT_YV12:
    case SDL_PIXELFORMAT_IYUV:
        *internalFormat = GL_LUMINANCE;
        *format = GL_LUMINANCE;
        *type = GL_UNSIGNED_BYTE;
        break;
#ifdef __MACOSX__
    case SDL_PIXELFORMAT_UYVY:
		*internalFormat = GL_RGB8;
		*format = GL_YCBCR_422_APPLE;
		*type = GL_UNSIGNED_SHORT_8_8_APPLE;
		break;
#endif
    default:
        return SDL_FALSE;
    }
