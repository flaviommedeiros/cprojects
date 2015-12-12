return "libopus " PACKAGE_VERSION
#ifdef OPUS_FIXED_POINT
          "-fixed"
#endif
#ifdef FUZZING
          "-fuzzing"
#endif
          ;
