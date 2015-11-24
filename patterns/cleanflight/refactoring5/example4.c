#ifdef GPS
if (feature(FEATURE_GPS)) {
                    blackboxSetState(BLACKBOX_STATE_SEND_GPS_H_HEADER);
                } else
#endif
                    blackboxSetState(BLACKBOX_STATE_SEND_SLOW_HEADER);
