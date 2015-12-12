if (ret == AVERROR(EINVAL)
#ifdef ENODATA
                    || ret == AVERROR(ENODATA)
#endif
                ) {
                    tpf = &streamparm.parm.capture.timeperframe;
                    break;
                }
