#ifndef MNG_NO_16BIT_SUPPORT
if (bTargetRGBA16)
              iTargetrowsize       = (iTargetsamples << 3);
            else
#endif
              iTargetrowsize       = (iTargetsamples << 2);
