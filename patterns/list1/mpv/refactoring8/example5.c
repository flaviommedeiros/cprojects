CGLPixelFormatAttribute attrs[] = {
        kCGLPFAOpenGLProfile,
        (CGLPixelFormatAttribute) version,
        kCGLPFADoubleBuffer,
        kCGLPFAAccelerated,
        #if MAC_OS_X_VERSION_MIN_REQUIRED >= MAC_OS_X_VERSION_10_8
        // leave this as the last entry of the array to not break the fallback
        // code
        kCGLPFASupportsAutomaticGraphicsSwitching,
        #endif
        0
    };
