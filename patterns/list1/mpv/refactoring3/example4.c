switch (format) {
    case AF_FORMAT_S_AC3:   return PA_ENCODING_AC3_IEC61937;
    case AF_FORMAT_S_EAC3:  return PA_ENCODING_EAC3_IEC61937;
    case AF_FORMAT_S_MP3:   return PA_ENCODING_MPEG_IEC61937;
    case AF_FORMAT_S_DTS:
    case AF_FORMAT_S_DTSHD: return PA_ENCODING_DTS_IEC61937;
#ifdef PA_ENCODING_MPEG2_AAC_IEC61937
    case AF_FORMAT_S_AAC:   return PA_ENCODING_MPEG2_AAC_IEC61937;
#endif
    default:
        if (af_fmt_is_spdif(format))
            return PA_ENCODING_ANY;
        return PA_ENCODING_PCM;
    }
