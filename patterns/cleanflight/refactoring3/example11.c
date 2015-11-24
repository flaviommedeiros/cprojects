switch (cmdMSP) {
    case MSP_API_VERSION:
        headSerialReply(
            1 + // protocol version length
            API_VERSION_LENGTH
        );
        serialize8(MSP_PROTOCOL_VERSION);

        serialize8(API_VERSION_MAJOR);
        serialize8(API_VERSION_MINOR);
        break;

    case MSP_FC_VARIANT:
        headSerialReply(FLIGHT_CONTROLLER_IDENTIFIER_LENGTH);

        for (i = 0; i < FLIGHT_CONTROLLER_IDENTIFIER_LENGTH; i++) {
            serialize8(flightControllerIdentifier[i]);
        }
        break;

    case MSP_FC_VERSION:
        headSerialReply(FLIGHT_CONTROLLER_VERSION_LENGTH);

        serialize8(FC_VERSION_MAJOR);
        serialize8(FC_VERSION_MINOR);
        serialize8(FC_VERSION_PATCH_LEVEL);
        break;

    case MSP_BOARD_INFO:
        headSerialReply(
            BOARD_IDENTIFIER_LENGTH +
            BOARD_HARDWARE_REVISION_LENGTH
        );
        for (i = 0; i < BOARD_IDENTIFIER_LENGTH; i++) {
            serialize8(boardIdentifier[i]);
        }
#ifdef NAZE
        serialize16(hardwareRevision);
#else
        serialize16(0); // No other build targets currently have hardware revision detection.
#endif
        break;

    case MSP_BUILD_INFO:
        headSerialReply(
                BUILD_DATE_LENGTH +
                BUILD_TIME_LENGTH +
                GIT_SHORT_REVISION_LENGTH
        );

        for (i = 0; i < BUILD_DATE_LENGTH; i++) {
            serialize8(buildDate[i]);
        }
        for (i = 0; i < BUILD_TIME_LENGTH; i++) {
            serialize8(buildTime[i]);
        }

        for (i = 0; i < GIT_SHORT_REVISION_LENGTH; i++) {
            serialize8(shortGitRevision[i]);
        }
        break;

    // DEPRECATED - Use MSP_API_VERSION
    case MSP_IDENT:
        headSerialReply(7);
        serialize8(MW_VERSION);
        serialize8(masterConfig.mixerMode);
        serialize8(MSP_PROTOCOL_VERSION);
        serialize32(CAP_DYNBALANCE); // "capability"
        break;

    case MSP_STATUS:
        headSerialReply(11);
        serialize16(cycleTime);
#ifdef USE_I2C
        serialize16(i2cGetErrorCounter());
#else
        serialize16(0);
#endif
        serialize16(sensors(SENSOR_ACC) | sensors(SENSOR_BARO) << 1 | sensors(SENSOR_MAG) << 2 | sensors(SENSOR_GPS) << 3 | sensors(SENSOR_SONAR) << 4);
        // Serialize the flags in the order we delivered them, ignoring BOXNAMES and BOXINDEXES
        // Requires new Multiwii protocol version to fix
        // It would be preferable to setting the enabled bits based on BOXINDEX.
        junk = 0;
        tmp = IS_ENABLED(FLIGHT_MODE(ANGLE_MODE)) << BOXANGLE |
            IS_ENABLED(FLIGHT_MODE(HORIZON_MODE)) << BOXHORIZON |
            IS_ENABLED(FLIGHT_MODE(BARO_MODE)) << BOXBARO |
            IS_ENABLED(FLIGHT_MODE(MAG_MODE)) << BOXMAG |
            IS_ENABLED(FLIGHT_MODE(HEADFREE_MODE)) << BOXHEADFREE |
            IS_ENABLED(IS_RC_MODE_ACTIVE(BOXHEADADJ)) << BOXHEADADJ |
            IS_ENABLED(IS_RC_MODE_ACTIVE(BOXCAMSTAB)) << BOXCAMSTAB |
            IS_ENABLED(IS_RC_MODE_ACTIVE(BOXCAMTRIG)) << BOXCAMTRIG |
            IS_ENABLED(FLIGHT_MODE(GPS_HOME_MODE)) << BOXGPSHOME |
            IS_ENABLED(FLIGHT_MODE(GPS_HOLD_MODE)) << BOXGPSHOLD |
            IS_ENABLED(FLIGHT_MODE(PASSTHRU_MODE)) << BOXPASSTHRU |
            IS_ENABLED(IS_RC_MODE_ACTIVE(BOXBEEPERON)) << BOXBEEPERON |
            IS_ENABLED(IS_RC_MODE_ACTIVE(BOXLEDMAX)) << BOXLEDMAX |
            IS_ENABLED(IS_RC_MODE_ACTIVE(BOXLEDLOW)) << BOXLEDLOW |
            IS_ENABLED(IS_RC_MODE_ACTIVE(BOXLLIGHTS)) << BOXLLIGHTS |
            IS_ENABLED(IS_RC_MODE_ACTIVE(BOXCALIB)) << BOXCALIB |
            IS_ENABLED(IS_RC_MODE_ACTIVE(BOXGOV)) << BOXGOV |
            IS_ENABLED(IS_RC_MODE_ACTIVE(BOXOSD)) << BOXOSD |
            IS_ENABLED(IS_RC_MODE_ACTIVE(BOXTELEMETRY)) << BOXTELEMETRY |
            IS_ENABLED(IS_RC_MODE_ACTIVE(BOXGTUNE)) << BOXGTUNE |
            IS_ENABLED(FLIGHT_MODE(SONAR_MODE)) << BOXSONAR |
            IS_ENABLED(ARMING_FLAG(ARMED)) << BOXARM |
            IS_ENABLED(IS_RC_MODE_ACTIVE(BOXBLACKBOX)) << BOXBLACKBOX |
            IS_ENABLED(FLIGHT_MODE(FAILSAFE_MODE)) << BOXFAILSAFE;
        for (i = 0; i < activeBoxIdCount; i++) {
            int flag = (tmp & (1 << activeBoxIds[i]));
            if (flag)
                junk |= 1 << i;
        }
        serialize32(junk);
        serialize8(masterConfig.current_profile_index);
        break;
    case MSP_RAW_IMU:
        headSerialReply(18);

        // Hack scale due to choice of units for sensor data in multiwii
        uint8_t scale = (acc_1G > 1024) ? 8 : 1;

        for (i = 0; i < 3; i++)
            serialize16(accSmooth[i] / scale);
        for (i = 0; i < 3; i++)
            serialize16(gyroADC[i]);
        for (i = 0; i < 3; i++)
            serialize16(magADC[i]);
        break;
#ifdef USE_SERVOS
    case MSP_SERVO:
        s_struct((uint8_t *)&servo, MAX_SUPPORTED_SERVOS * 2);
        break;
    case MSP_SERVO_CONFIGURATIONS:
        headSerialReply(MAX_SUPPORTED_SERVOS * sizeof(servoParam_t));
        for (i = 0; i < MAX_SUPPORTED_SERVOS; i++) {
            serialize16(currentProfile->servoConf[i].min);
            serialize16(currentProfile->servoConf[i].max);
            serialize16(currentProfile->servoConf[i].middle);
            serialize8(currentProfile->servoConf[i].rate);
            serialize8(currentProfile->servoConf[i].angleAtMin);
            serialize8(currentProfile->servoConf[i].angleAtMax);
            serialize8(currentProfile->servoConf[i].forwardFromChannel);
            serialize32(currentProfile->servoConf[i].reversedSources);
        }
        break;
    case MSP_SERVO_MIX_RULES:
        headSerialReply(MAX_SERVO_RULES * sizeof(servoMixer_t));
        for (i = 0; i < MAX_SERVO_RULES; i++) {
            serialize8(masterConfig.customServoMixer[i].targetChannel);
            serialize8(masterConfig.customServoMixer[i].inputSource);
            serialize8(masterConfig.customServoMixer[i].rate);
            serialize8(masterConfig.customServoMixer[i].speed);
            serialize8(masterConfig.customServoMixer[i].min);
            serialize8(masterConfig.customServoMixer[i].max);
            serialize8(masterConfig.customServoMixer[i].box);
        }
        break;
#endif
    case MSP_MOTOR:
        s_struct((uint8_t *)motor, 16);
        break;
    case MSP_RC:
        headSerialReply(2 * rxRuntimeConfig.channelCount);
        for (i = 0; i < rxRuntimeConfig.channelCount; i++)
            serialize16(rcData[i]);
        break;
    case MSP_ATTITUDE:
        headSerialReply(6);
        for (i = 0; i < 2; i++)
            serialize16(inclination.raw[i]);
        serialize16(heading);
        break;
    case MSP_ALTITUDE:
        headSerialReply(6);
#if defined(BARO) || defined(SONAR)
        serialize32(altitudeHoldGetEstimatedAltitude());
#else
        serialize32(0);
#endif
        serialize16(vario);
        break;
    case MSP_SONAR_ALTITUDE:
        headSerialReply(4);
#if defined(SONAR)
        serialize32(sonarGetLatestAltitude());
#else
        serialize32(0);
#endif
        break;
    case MSP_ANALOG:
        headSerialReply(7);
        serialize8((uint8_t)constrain(vbat, 0, 255));
        serialize16((uint16_t)constrain(mAhDrawn, 0, 0xFFFF)); // milliamp hours drawn from battery
        serialize16(rssi);
        if(masterConfig.batteryConfig.multiwiiCurrentMeterOutput) {
            serialize16((uint16_t)constrain(amperage * 10, 0, 0xFFFF)); // send amperage in 0.001 A steps. Negative range is truncated to zero
        } else
            serialize16((int16_t)constrain(amperage, -0x8000, 0x7FFF)); // send amperage in 0.01 A steps, range is -320A to 320A
        break;
    case MSP_ARMING_CONFIG:
        headSerialReply(2);
        serialize8(masterConfig.auto_disarm_delay); 
        serialize8(masterConfig.disarm_kill_switch);
        break;
    case MSP_LOOP_TIME:
        headSerialReply(2);
        serialize16(masterConfig.looptime);
        break;
    case MSP_RC_TUNING:
        headSerialReply(11);
        serialize8(currentControlRateProfile->rcRate8);
        serialize8(currentControlRateProfile->rcExpo8);
        for (i = 0 ; i < 3; i++) {
            serialize8(currentControlRateProfile->rates[i]); // R,P,Y see flight_dynamics_index_t
        }
        serialize8(currentControlRateProfile->dynThrPID);
        serialize8(currentControlRateProfile->thrMid8);
        serialize8(currentControlRateProfile->thrExpo8);
        serialize16(currentControlRateProfile->tpa_breakpoint);
        serialize8(currentControlRateProfile->rcYawExpo8);
        break;
    case MSP_PID:
        headSerialReply(3 * PID_ITEM_COUNT);
        if (IS_PID_CONTROLLER_FP_BASED(currentProfile->pidProfile.pidController)) { // convert float stuff into uint8_t to keep backwards compatability with all 8-bit shit with new pid
            for (i = 0; i < 3; i++) {
                serialize8(constrain(lrintf(currentProfile->pidProfile.P_f[i] * 10.0f), 0, 255));
                serialize8(constrain(lrintf(currentProfile->pidProfile.I_f[i] * 100.0f), 0, 255));
                serialize8(constrain(lrintf(currentProfile->pidProfile.D_f[i] * 1000.0f), 0, 255));
            }
            for (i = 3; i < PID_ITEM_COUNT; i++) {
                if (i == PIDLEVEL) {
                    serialize8(constrain(lrintf(currentProfile->pidProfile.A_level * 10.0f), 0, 255));
                    serialize8(constrain(lrintf(currentProfile->pidProfile.H_level * 10.0f), 0, 255));
                    serialize8(constrain(lrintf(currentProfile->pidProfile.H_sensitivity), 0, 255));
                } else {
                    serialize8(currentProfile->pidProfile.P8[i]);
                    serialize8(currentProfile->pidProfile.I8[i]);
                    serialize8(currentProfile->pidProfile.D8[i]);
                }
            }
        } else {
            for (i = 0; i < PID_ITEM_COUNT; i++) {
                serialize8(currentProfile->pidProfile.P8[i]);
                serialize8(currentProfile->pidProfile.I8[i]);
                serialize8(currentProfile->pidProfile.D8[i]);
            }
        }
        break;
    case MSP_PIDNAMES:
        headSerialReply(sizeof(pidnames) - 1);
        serializeNames(pidnames);
        break;
    case MSP_PID_CONTROLLER:
        headSerialReply(1);
        serialize8(currentProfile->pidProfile.pidController);
        break;
    case MSP_MODE_RANGES:
        headSerialReply(4 * MAX_MODE_ACTIVATION_CONDITION_COUNT);
        for (i = 0; i < MAX_MODE_ACTIVATION_CONDITION_COUNT; i++) {
            modeActivationCondition_t *mac = &currentProfile->modeActivationConditions[i];
            const box_t *box = &boxes[mac->modeId];
            serialize8(box->permanentId);
            serialize8(mac->auxChannelIndex);
            serialize8(mac->range.startStep);
            serialize8(mac->range.endStep);
        }
        break;
    case MSP_ADJUSTMENT_RANGES:
        headSerialReply(MAX_ADJUSTMENT_RANGE_COUNT * (
                1 + // adjustment index/slot
                1 + // aux channel index
                1 + // start step
                1 + // end step
                1 + // adjustment function
                1   // aux switch channel index
        ));
        for (i = 0; i < MAX_ADJUSTMENT_RANGE_COUNT; i++) {
            adjustmentRange_t *adjRange = &currentProfile->adjustmentRanges[i];
            serialize8(adjRange->adjustmentIndex);
            serialize8(adjRange->auxChannelIndex);
            serialize8(adjRange->range.startStep);
            serialize8(adjRange->range.endStep);
            serialize8(adjRange->adjustmentFunction);
            serialize8(adjRange->auxSwitchChannelIndex);
        }
        break;
    case MSP_BOXNAMES:
        serializeBoxNamesReply();
        break;
    case MSP_BOXIDS:
        headSerialReply(activeBoxIdCount);
        for (i = 0; i < activeBoxIdCount; i++) {
            const box_t *box = findBoxByActiveBoxId(activeBoxIds[i]);
            if (!box) {
                continue;
            }
            serialize8(box->permanentId);
        }
        break;
    case MSP_MISC:
        headSerialReply(2 * 5 + 3 + 3 + 2 + 4);
        serialize16(masterConfig.rxConfig.midrc);

        serialize16(masterConfig.escAndServoConfig.minthrottle);
        serialize16(masterConfig.escAndServoConfig.maxthrottle);
        serialize16(masterConfig.escAndServoConfig.mincommand);

        serialize16(masterConfig.failsafeConfig.failsafe_throttle);

#ifdef GPS
        serialize8(masterConfig.gpsConfig.provider); // gps_type
        serialize8(0); // TODO gps_baudrate (an index, cleanflight uses a uint32_t
        serialize8(masterConfig.gpsConfig.sbasMode); // gps_ubx_sbas
#else
        serialize8(0); // gps_type
        serialize8(0); // TODO gps_baudrate (an index, cleanflight uses a uint32_t
        serialize8(0); // gps_ubx_sbas
#endif
        serialize8(masterConfig.batteryConfig.multiwiiCurrentMeterOutput);
        serialize8(masterConfig.rxConfig.rssi_channel);
        serialize8(0);

        serialize16(currentProfile->mag_declination / 10);

        serialize8(masterConfig.batteryConfig.vbatscale);
        serialize8(masterConfig.batteryConfig.vbatmincellvoltage);
        serialize8(masterConfig.batteryConfig.vbatmaxcellvoltage);
        serialize8(masterConfig.batteryConfig.vbatwarningcellvoltage);
        break;

    case MSP_MOTOR_PINS:
        // FIXME This is hardcoded and should not be.
        headSerialReply(8);
        for (i = 0; i < 8; i++)
            serialize8(i + 1);
        break;
#ifdef GPS
    case MSP_RAW_GPS:
        headSerialReply(16);
        serialize8(STATE(GPS_FIX));
        serialize8(GPS_numSat);
        serialize32(GPS_coord[LAT]);
        serialize32(GPS_coord[LON]);
        serialize16(GPS_altitude);
        serialize16(GPS_speed);
        serialize16(GPS_ground_course);
        break;
    case MSP_COMP_GPS:
        headSerialReply(5);
        serialize16(GPS_distanceToHome);
        serialize16(GPS_directionToHome);
        serialize8(GPS_update & 1);
        break;
    case MSP_WP:
        wp_no = read8();    // get the wp number
        headSerialReply(18);
        if (wp_no == 0) {
            lat = GPS_home[LAT];
            lon = GPS_home[LON];
        } else if (wp_no == 16) {
            lat = GPS_hold[LAT];
            lon = GPS_hold[LON];
        }
        serialize8(wp_no);
        serialize32(lat);
        serialize32(lon);
        serialize32(AltHold);           // altitude (cm) will come here -- temporary implementation to test feature with apps
        serialize16(0);                 // heading  will come here (deg)
        serialize16(0);                 // time to stay (ms) will come here
        serialize8(0);                  // nav flag will come here
        break;
    case MSP_GPSSVINFO:
        headSerialReply(1 + (GPS_numCh * 4));
        serialize8(GPS_numCh);
           for (i = 0; i < GPS_numCh; i++){
               serialize8(GPS_svinfo_chn[i]);
               serialize8(GPS_svinfo_svid[i]);
               serialize8(GPS_svinfo_quality[i]);
               serialize8(GPS_svinfo_cno[i]);
           }
        break;
#endif
    case MSP_DEBUG:
        headSerialReply(DEBUG16_VALUE_COUNT * sizeof(debug[0]));

        // output some useful QA statistics
        // debug[x] = ((hse_value / 1000000) * 1000) + (SystemCoreClock / 1000000);         // XX0YY [crystal clock : core clock]

        for (i = 0; i < DEBUG16_VALUE_COUNT; i++)
            serialize16(debug[i]);      // 4 variables are here for general monitoring purpose
        break;

    // Additional commands that are not compatible with MultiWii
    case MSP_ACC_TRIM:
        headSerialReply(4);
        serialize16(currentProfile->accelerometerTrims.values.pitch);
        serialize16(currentProfile->accelerometerTrims.values.roll);
        break;

    case MSP_UID:
        headSerialReply(12);
        serialize32(U_ID_0);
        serialize32(U_ID_1);
        serialize32(U_ID_2);
        break;

    case MSP_FEATURE:
        headSerialReply(4);
        serialize32(featureMask());
        break;

    case MSP_BOARD_ALIGNMENT:
        headSerialReply(6);
        serialize16(masterConfig.boardAlignment.rollDegrees);
        serialize16(masterConfig.boardAlignment.pitchDegrees);
        serialize16(masterConfig.boardAlignment.yawDegrees);
        break;

    case MSP_VOLTAGE_METER_CONFIG:
        headSerialReply(4);
        serialize8(masterConfig.batteryConfig.vbatscale);
        serialize8(masterConfig.batteryConfig.vbatmincellvoltage);
        serialize8(masterConfig.batteryConfig.vbatmaxcellvoltage);
        serialize8(masterConfig.batteryConfig.vbatwarningcellvoltage);
        break;

    case MSP_CURRENT_METER_CONFIG:
        headSerialReply(7);
        serialize16(masterConfig.batteryConfig.currentMeterScale);
        serialize16(masterConfig.batteryConfig.currentMeterOffset);
        serialize8(masterConfig.batteryConfig.currentMeterType);
        serialize16(masterConfig.batteryConfig.batteryCapacity);
        break;

    case MSP_MIXER:
        headSerialReply(1);
        serialize8(masterConfig.mixerMode);
        break;

    case MSP_RX_CONFIG:
        headSerialReply(12);
        serialize8(masterConfig.rxConfig.serialrx_provider);
        serialize16(masterConfig.rxConfig.maxcheck);
        serialize16(masterConfig.rxConfig.midrc);
        serialize16(masterConfig.rxConfig.mincheck);
        serialize8(masterConfig.rxConfig.spektrum_sat_bind);
        serialize16(masterConfig.rxConfig.rx_min_usec);
        serialize16(masterConfig.rxConfig.rx_max_usec);
        break;

    case MSP_FAILSAFE_CONFIG:
        headSerialReply(4);
        serialize8(masterConfig.failsafeConfig.failsafe_delay);
        serialize8(masterConfig.failsafeConfig.failsafe_off_delay);
        serialize16(masterConfig.failsafeConfig.failsafe_throttle);
        break;

    case MSP_RXFAIL_CONFIG:
        headSerialReply(3 * (rxRuntimeConfig.channelCount));
        for (i = 0; i < rxRuntimeConfig.channelCount; i++) {
            serialize8(masterConfig.rxConfig.failsafe_channel_configurations[i].mode);
            serialize16(RXFAIL_STEP_TO_CHANNEL_VALUE(masterConfig.rxConfig.failsafe_channel_configurations[i].step));
        }
        break;

    case MSP_RSSI_CONFIG:
        headSerialReply(1);
        serialize8(masterConfig.rxConfig.rssi_channel);
        break;

    case MSP_RX_MAP:
        headSerialReply(MAX_MAPPABLE_RX_INPUTS);
        for (i = 0; i < MAX_MAPPABLE_RX_INPUTS; i++)
            serialize8(masterConfig.rxConfig.rcmap[i]);
        break;

    case MSP_BF_CONFIG:
        headSerialReply(1 + 4 + 1 + 2 + 2 + 2 + 2 + 2);
        serialize8(masterConfig.mixerMode);

        serialize32(featureMask());

        serialize8(masterConfig.rxConfig.serialrx_provider);

        serialize16(masterConfig.boardAlignment.rollDegrees);
        serialize16(masterConfig.boardAlignment.pitchDegrees);
        serialize16(masterConfig.boardAlignment.yawDegrees);

        serialize16(masterConfig.batteryConfig.currentMeterScale);
        serialize16(masterConfig.batteryConfig.currentMeterOffset);
        break;

    case MSP_CF_SERIAL_CONFIG:
        headSerialReply(
            ((sizeof(uint8_t) + sizeof(uint16_t) + (sizeof(uint8_t) * 4)) * serialGetAvailablePortCount())
        );
        for (i = 0; i < SERIAL_PORT_COUNT; i++) {
            if (!serialIsPortAvailable(masterConfig.serialConfig.portConfigs[i].identifier)) {
                continue;
            };
            serialize8(masterConfig.serialConfig.portConfigs[i].identifier);
            serialize16(masterConfig.serialConfig.portConfigs[i].functionMask);
            serialize8(masterConfig.serialConfig.portConfigs[i].msp_baudrateIndex);
            serialize8(masterConfig.serialConfig.portConfigs[i].gps_baudrateIndex);
            serialize8(masterConfig.serialConfig.portConfigs[i].telemetry_baudrateIndex);
            serialize8(masterConfig.serialConfig.portConfigs[i].blackbox_baudrateIndex);
        }
        break;

#ifdef LED_STRIP
    case MSP_LED_COLORS:
        headSerialReply(CONFIGURABLE_COLOR_COUNT * 4);
        for (i = 0; i < CONFIGURABLE_COLOR_COUNT; i++) {
            hsvColor_t *color = &masterConfig.colors[i];
            serialize16(color->h);
            serialize8(color->s);
            serialize8(color->v);
        }
        break;

    case MSP_LED_STRIP_CONFIG:
        headSerialReply(MAX_LED_STRIP_LENGTH * 7);
        for (i = 0; i < MAX_LED_STRIP_LENGTH; i++) {
            ledConfig_t *ledConfig = &masterConfig.ledConfigs[i];
            serialize16((ledConfig->flags & LED_DIRECTION_MASK) >> LED_DIRECTION_BIT_OFFSET);
            serialize16((ledConfig->flags & LED_FUNCTION_MASK) >> LED_FUNCTION_BIT_OFFSET);
            serialize8(GET_LED_X(ledConfig));
            serialize8(GET_LED_Y(ledConfig));
            serialize8(ledConfig->color);
        }
        break;
#endif

    case MSP_DATAFLASH_SUMMARY:
        serializeDataflashSummaryReply();
        break;

#ifdef USE_FLASHFS
    case MSP_DATAFLASH_READ:
        {
            uint32_t readAddress = read32();

            serializeDataflashReadReply(readAddress, 128);
        }
        break;
#endif

    case MSP_BF_BUILD_INFO:
        headSerialReply(11 + 4 + 4);
        for (i = 0; i < 11; i++)
        serialize8(buildDate[i]); // MMM DD YYYY as ascii, MMM = Jan/Feb... etc
        serialize32(0); // future exp
        serialize32(0); // future exp
        break;

    case MSP_3D:
        headSerialReply(2 * 4);
        serialize16(masterConfig.flight3DConfig.deadband3d_low);
        serialize16(masterConfig.flight3DConfig.deadband3d_high);
        serialize16(masterConfig.flight3DConfig.neutral3d);
        serialize16(masterConfig.flight3DConfig.deadband3d_throttle);
        break;

    default:
        return false;
    }
