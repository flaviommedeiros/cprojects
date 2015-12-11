return "libopus " PACKAGE_VERSION
#ifdef FIXED_POINT
          "-fixed"
#endif
#ifdef FUZZING
          "-fuzzing"
#endif
          ;
