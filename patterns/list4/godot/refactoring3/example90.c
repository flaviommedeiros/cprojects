switch (uv_csp) {
        case WEBP_YUV420:
          break;
#ifdef WEBP_EXPERIMENTAL_FEATURES
        case WEBP_YUV400:    // for now, we'll just reset the U/V samples
          break;
        case WEBP_YUV422:
          uv0_stride = uv_width;
          break;
        case WEBP_YUV444:
          uv0_stride = width;
          break;
#endif
        default:
          return 0;
      }
