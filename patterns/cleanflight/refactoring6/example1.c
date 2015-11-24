if (false
#if defined(BARO)
            || (sensors(SENSOR_BARO) && isBaroReady())
#endif
#if defined(SONAR)
            || sensors(SENSOR_SONAR)
#endif
            ) {
            calculateEstimatedAltitude(currentTime);
        }
