switch (periodicTaskIndex++) {
#ifdef MAG
    case UPDATE_COMPASS_TASK:
        if (sensors(SENSOR_MAG)) {
            updateCompass(&masterConfig.magZero);
        }
        break;
#endif

#ifdef BARO
    case UPDATE_BARO_TASK:
        if (sensors(SENSOR_BARO)) {
            baroUpdate(currentTime);
        }
        break;
#endif

#if defined(BARO) || defined(SONAR)
    case CALCULATE_ALTITUDE_TASK:
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
        break;
#endif
#ifdef SONAR
    case UPDATE_SONAR_TASK:
        if (sensors(SENSOR_SONAR)) {
            sonarUpdate();
        }
        break;
#endif
#ifdef DISPLAY
    case UPDATE_DISPLAY_TASK:
        if (feature(FEATURE_DISPLAY)) {
            updateDisplay();
        }
        break;
#endif
    }
