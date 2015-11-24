switch(id) {
#ifdef GPS
            case FSSP_DATAID_SPEED      :
                if (sensors(SENSOR_GPS) && STATE(GPS_FIX)) {
                    uint32_t tmpui = (GPS_speed * 36 + 36 / 2) / 100;
                    smartPortSendPackage(id, tmpui); // given in 0.1 m/s, provide in KM/H
                    smartPortHasRequest = 0;
                }
                break;
#endif
            case FSSP_DATAID_VFAS       :
                if (feature(FEATURE_VBAT)) {
                    smartPortSendPackage(id, vbat * 10); // given in 0.1V, convert to volts
                    smartPortHasRequest = 0;
                }
                break;
            case FSSP_DATAID_CURRENT    :
                if (feature(FEATURE_CURRENT_METER)) {
                    smartPortSendPackage(id, amperage / 10); // given in 10mA steps, unknown requested unit
                    smartPortHasRequest = 0;
                }
                break;
            //case FSSP_DATAID_RPM        :
            case FSSP_DATAID_ALTITUDE   :
                if (sensors(SENSOR_BARO)) {
                    smartPortSendPackage(id, BaroAlt); // unknown given unit, requested 100 = 1 meter
                    smartPortHasRequest = 0;
                }
                break;
            case FSSP_DATAID_FUEL       :
                if (feature(FEATURE_CURRENT_METER)) {
                    smartPortSendPackage(id, mAhDrawn); // given in mAh, unknown requested unit
                    smartPortHasRequest = 0;
                }
                break;
            //case FSSP_DATAID_ADC1       :
            //case FSSP_DATAID_ADC2       :
#ifdef GPS
            case FSSP_DATAID_LATLONG    :
                if (sensors(SENSOR_GPS) && STATE(GPS_FIX)) {
                    uint32_t tmpui = 0;
                    // the same ID is sent twice, one for longitude, one for latitude
                    // the MSB of the sent uint32_t helps FrSky keep track
                    // the even/odd bit of our counter helps us keep track
                    if (smartPortIdCnt & 1) {
                        tmpui = abs(GPS_coord[LON]);  // now we have unsigned value and one bit to spare
                        tmpui = (tmpui + tmpui / 2) / 25 | 0x80000000;  // 6/100 = 1.5/25, division by power of 2 is fast
                        if (GPS_coord[LON] < 0) tmpui |= 0x40000000;
                    }
                    else {
                        tmpui = abs(GPS_coord[LAT]);  // now we have unsigned value and one bit to spare
                        tmpui = (tmpui + tmpui / 2) / 25;  // 6/100 = 1.5/25, division by power of 2 is fast
                        if (GPS_coord[LAT] < 0) tmpui |= 0x40000000;
                    }
                    smartPortSendPackage(id, tmpui);
                    smartPortHasRequest = 0;
                }
                break;
#endif
            //case FSSP_DATAID_CAP_USED   :
            case FSSP_DATAID_VARIO      :
                if (sensors(SENSOR_BARO)) {
                    smartPortSendPackage(id, vario); // unknown given unit but requested in 100 = 1m/s
                    smartPortHasRequest = 0;
                }
                break;
            case FSSP_DATAID_HEADING    :
                smartPortSendPackage(id, heading * 100); // given in deg, requested in 10000 = 100 deg
                smartPortHasRequest = 0;
                break;
            case FSSP_DATAID_ACCX       :
                smartPortSendPackage(id, accSmooth[X] / 44);
                // unknown input and unknown output unit
                // we can only show 00.00 format, another digit won't display right on Taranis
                // dividing by roughly 44 will give acceleration in G units
                smartPortHasRequest = 0;
                break;
            case FSSP_DATAID_ACCY       :
                smartPortSendPackage(id, accSmooth[Y] / 44);
                smartPortHasRequest = 0;
                break;
            case FSSP_DATAID_ACCZ       :
                smartPortSendPackage(id, accSmooth[Z] / 44);
                smartPortHasRequest = 0;
                break;
            case FSSP_DATAID_T1         :
                // we send all the flags as decimal digits for easy reading

                // the t1Cnt simply allows the telemetry view to show at least some changes
                t1Cnt++;
                if (t1Cnt >= 4) {
                    t1Cnt = 1;
                }
                tmpi = t1Cnt * 10000; // start off with at least one digit so the most significant 0 won't be cut off
                // the Taranis seems to be able to fit 5 digits on the screen
                // the Taranis seems to consider this number a signed 16 bit integer

                if (ARMING_FLAG(OK_TO_ARM))
                    tmpi += 1;
                if (ARMING_FLAG(PREVENT_ARMING))
                    tmpi += 2;
                if (ARMING_FLAG(ARMED))
                    tmpi += 4;

                if (FLIGHT_MODE(ANGLE_MODE))
                    tmpi += 10;
                if (FLIGHT_MODE(HORIZON_MODE))
                    tmpi += 20;
                if (FLIGHT_MODE(UNUSED_MODE))
                    tmpi += 40;
                if (FLIGHT_MODE(PASSTHRU_MODE))
                    tmpi += 40;

                if (FLIGHT_MODE(MAG_MODE))
                    tmpi += 100;
                if (FLIGHT_MODE(BARO_MODE))
                    tmpi += 200;
                if (FLIGHT_MODE(SONAR_MODE))
                    tmpi += 400;

                if (FLIGHT_MODE(GPS_HOLD_MODE))
                    tmpi += 1000;
                if (FLIGHT_MODE(GPS_HOME_MODE))
                    tmpi += 2000;
                if (FLIGHT_MODE(HEADFREE_MODE))
                    tmpi += 4000;

                smartPortSendPackage(id, (uint32_t)tmpi);
                smartPortHasRequest = 0;
                break;
            case FSSP_DATAID_T2         :
                if (sensors(SENSOR_GPS)) {
#ifdef GPS
                    // provide GPS lock status
                    smartPortSendPackage(id, (STATE(GPS_FIX) ? 1000 : 0) + (STATE(GPS_FIX_HOME) ? 2000 : 0) + GPS_numSat);
                    smartPortHasRequest = 0;
#endif
                }
                else if (feature(FEATURE_GPS)) {
                    smartPortSendPackage(id, 0);
                    smartPortHasRequest = 0;
                }
                break;
#ifdef GPS
            case FSSP_DATAID_GPS_ALT    :
                if (sensors(SENSOR_GPS) && STATE(GPS_FIX)) {
                    smartPortSendPackage(id, GPS_altitude * 100); // given in 0.1m , requested in 10 = 1m (should be in mm, probably a bug in opentx, tested on 2.0.1.7)
                    smartPortHasRequest = 0;
                }
                break;
#endif
            default:
                break;
                // if nothing is sent, smartPortHasRequest isn't cleared, we already incremented the counter, just loop back to the start
        }
