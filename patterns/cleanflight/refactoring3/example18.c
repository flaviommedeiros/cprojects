switch (currentPort->cmdMSP) {
    case MSP_SELECT_SETTING:
        if (!ARMING_FLAG(ARMED)) {
            masterConfig.current_profile_index = read8();
            if (masterConfig.current_profile_index > 2) {
                masterConfig.current_profile_index = 0;
            }
            writeEEPROM();
            readEEPROM();
        }
        break;
    case MSP_SET_HEAD:
        magHold = read16();
        break;
    case MSP_SET_RAW_RC:
        {
            uint8_t channelCount = currentPort->dataSize / sizeof(uint16_t);
            if (channelCount > MAX_SUPPORTED_RC_CHANNEL_COUNT) {
                headSerialError(0);
            } else {
                uint16_t frame[MAX_SUPPORTED_RC_CHANNEL_COUNT];

                for (i = 0; i < channelCount; i++) {
                    frame[i] = read16();
                }

                rxMspFrameReceive(frame, channelCount);
            }
        }
        break;
    case MSP_SET_ACC_TRIM:
        currentProfile->accelerometerTrims.values.pitch = read16();
        currentProfile->accelerometerTrims.values.roll  = read16();
        break;
    case MSP_SET_ARMING_CONFIG:
        masterConfig.auto_disarm_delay = read8();
        masterConfig.disarm_kill_switch = read8();
        break;
    case MSP_SET_LOOP_TIME:
        masterConfig.looptime = read16();
        break;
    case MSP_SET_PID_CONTROLLER:
        currentProfile->pidProfile.pidController = read8();
        pidSetController(currentProfile->pidProfile.pidController);
        break;
    case MSP_SET_PID:
        if (IS_PID_CONTROLLER_FP_BASED(currentProfile->pidProfile.pidController)) {
            for (i = 0; i < 3; i++) {
                currentProfile->pidProfile.P_f[i] = (float)read8() / 10.0f;
                currentProfile->pidProfile.I_f[i] = (float)read8() / 100.0f;
                currentProfile->pidProfile.D_f[i] = (float)read8() / 1000.0f;
            }
            for (i = 3; i < PID_ITEM_COUNT; i++) {
                if (i == PIDLEVEL) {
                    currentProfile->pidProfile.A_level = (float)read8() / 10.0f;
                    currentProfile->pidProfile.H_level = (float)read8() / 10.0f;
                    currentProfile->pidProfile.H_sensitivity = read8();
                } else {
                    currentProfile->pidProfile.P8[i] = read8();
                    currentProfile->pidProfile.I8[i] = read8();
                    currentProfile->pidProfile.D8[i] = read8();
                }
            }
        } else {
            for (i = 0; i < PID_ITEM_COUNT; i++) {
                currentProfile->pidProfile.P8[i] = read8();
                currentProfile->pidProfile.I8[i] = read8();
                currentProfile->pidProfile.D8[i] = read8();
            }
        }
        break;
    case MSP_SET_MODE_RANGE:
        i = read8();
        if (i < MAX_MODE_ACTIVATION_CONDITION_COUNT) {
            modeActivationCondition_t *mac = &currentProfile->modeActivationConditions[i];
            i = read8();
            const box_t *box = findBoxByPermenantId(i);
            if (box) {
                mac->modeId = box->boxId;
                mac->auxChannelIndex = read8();
                mac->range.startStep = read8();
                mac->range.endStep = read8();

                useRcControlsConfig(currentProfile->modeActivationConditions, &masterConfig.escAndServoConfig, &currentProfile->pidProfile);
            } else {
                headSerialError(0);
            }
        } else {
            headSerialError(0);
        }
        break;
    case MSP_SET_ADJUSTMENT_RANGE:
        i = read8();
        if (i < MAX_ADJUSTMENT_RANGE_COUNT) {
            adjustmentRange_t *adjRange = &currentProfile->adjustmentRanges[i];
            i = read8();
            if (i < MAX_SIMULTANEOUS_ADJUSTMENT_COUNT) {
                adjRange->adjustmentIndex = i;
                adjRange->auxChannelIndex = read8();
                adjRange->range.startStep = read8();
                adjRange->range.endStep = read8();
                adjRange->adjustmentFunction = read8();
                adjRange->auxSwitchChannelIndex = read8();
            } else {
                headSerialError(0);
            }
        } else {
            headSerialError(0);
        }
        break;

    case MSP_SET_RC_TUNING:
        if (currentPort->dataSize >= 10) {
            currentControlRateProfile->rcRate8 = read8();
            currentControlRateProfile->rcExpo8 = read8();
            for (i = 0; i < 3; i++) {
                rate = read8();
                currentControlRateProfile->rates[i] = MIN(rate, i == FD_YAW ? CONTROL_RATE_CONFIG_YAW_RATE_MAX : CONTROL_RATE_CONFIG_ROLL_PITCH_RATE_MAX);
            }
            rate = read8();
            currentControlRateProfile->dynThrPID = MIN(rate, CONTROL_RATE_CONFIG_TPA_MAX);
            currentControlRateProfile->thrMid8 = read8();
            currentControlRateProfile->thrExpo8 = read8();
            currentControlRateProfile->tpa_breakpoint = read16();
            if (currentPort->dataSize >= 11) {
                currentControlRateProfile->rcYawExpo8 = read8();
            }
        } else {
            headSerialError(0);
        }
        break;
    case MSP_SET_MISC:
        tmp = read16();
        if (tmp < 1600 && tmp > 1400)
            masterConfig.rxConfig.midrc = tmp;

        masterConfig.escAndServoConfig.minthrottle = read16();
        masterConfig.escAndServoConfig.maxthrottle = read16();
        masterConfig.escAndServoConfig.mincommand = read16();

        masterConfig.failsafeConfig.failsafe_throttle = read16();

#ifdef GPS
        masterConfig.gpsConfig.provider = read8(); // gps_type
        read8(); // gps_baudrate
        masterConfig.gpsConfig.sbasMode = read8(); // gps_ubx_sbas
#else
        read8(); // gps_type
        read8(); // gps_baudrate
        read8(); // gps_ubx_sbas
#endif
        masterConfig.batteryConfig.multiwiiCurrentMeterOutput = read8();
        masterConfig.rxConfig.rssi_channel = read8();
        read8();

        currentProfile->mag_declination = read16() * 10;

        masterConfig.batteryConfig.vbatscale = read8();           // actual vbatscale as intended
        masterConfig.batteryConfig.vbatmincellvoltage = read8();  // vbatlevel_warn1 in MWC2.3 GUI
        masterConfig.batteryConfig.vbatmaxcellvoltage = read8();  // vbatlevel_warn2 in MWC2.3 GUI
        masterConfig.batteryConfig.vbatwarningcellvoltage = read8();  // vbatlevel when buzzer starts to alert
        break;
    case MSP_SET_MOTOR:
        for (i = 0; i < 8; i++) // FIXME should this use MAX_MOTORS or MAX_SUPPORTED_MOTORS instead of 8
            motor_disarmed[i] = read16();
        break;
    case MSP_SET_SERVO_CONFIGURATION:
#ifdef USE_SERVOS
        if (currentPort->dataSize != 1 + sizeof(servoParam_t)) {
            headSerialError(0);
            break;
        }
        i = read8();
        if (i >= MAX_SUPPORTED_SERVOS) {
            headSerialError(0);
        } else {
            currentProfile->servoConf[i].min = read16();
            currentProfile->servoConf[i].max = read16();
            currentProfile->servoConf[i].middle = read16();
            currentProfile->servoConf[i].rate = read8();
            currentProfile->servoConf[i].angleAtMin = read8();
            currentProfile->servoConf[i].angleAtMax = read8();
            currentProfile->servoConf[i].forwardFromChannel = read8();
            currentProfile->servoConf[i].reversedSources = read32();
        }
#endif
        break;
        
    case MSP_SET_SERVO_MIX_RULE:
#ifdef USE_SERVOS
        i = read8();
        if (i >= MAX_SERVO_RULES) {
            headSerialError(0);
        } else {
            masterConfig.customServoMixer[i].targetChannel = read8();
            masterConfig.customServoMixer[i].inputSource = read8();
            masterConfig.customServoMixer[i].rate = read8();
            masterConfig.customServoMixer[i].speed = read8();
            masterConfig.customServoMixer[i].min = read8();
            masterConfig.customServoMixer[i].max = read8();
            masterConfig.customServoMixer[i].box = read8();
            loadCustomServoMixer();
        }
#endif
        break;

    case MSP_SET_3D:
        masterConfig.flight3DConfig.deadband3d_low = read16();
        masterConfig.flight3DConfig.deadband3d_high = read16();
        masterConfig.flight3DConfig.neutral3d = read16();
        masterConfig.flight3DConfig.deadband3d_throttle = read16();
        break;
        
    case MSP_RESET_CONF:
        if (!ARMING_FLAG(ARMED)) {
            resetEEPROM();
            readEEPROM();
        }
        break;
    case MSP_ACC_CALIBRATION:
        if (!ARMING_FLAG(ARMED))
            accSetCalibrationCycles(CALIBRATING_ACC_CYCLES);
        break;
    case MSP_MAG_CALIBRATION:
        if (!ARMING_FLAG(ARMED))
            ENABLE_STATE(CALIBRATE_MAG);
        break;
    case MSP_EEPROM_WRITE:
        if (ARMING_FLAG(ARMED)) {
            headSerialError(0);
            return true;
        }
        writeEEPROM();
        readEEPROM();
        break;

#ifdef USE_FLASHFS
    case MSP_DATAFLASH_ERASE:
        flashfsEraseCompletely();
        break;
#endif

#ifdef GPS
    case MSP_SET_RAW_GPS:
        if (read8()) {
            ENABLE_STATE(GPS_FIX);
        } else {
            DISABLE_STATE(GPS_FIX);
        }
        GPS_numSat = read8();
        GPS_coord[LAT] = read32();
        GPS_coord[LON] = read32();
        GPS_altitude = read16();
        GPS_speed = read16();
        GPS_update |= 2;        // New data signalisation to GPS functions // FIXME Magic Numbers
        break;
    case MSP_SET_WP:
        wp_no = read8();    //get the wp number
        lat = read32();
        lon = read32();
        alt = read32();     // to set altitude (cm)
        read16();           // future: to set heading (deg)
        read16();           // future: to set time to stay (ms)
        read8();            // future: to set nav flag
        if (wp_no == 0) {
            GPS_home[LAT] = lat;
            GPS_home[LON] = lon;
            DISABLE_FLIGHT_MODE(GPS_HOME_MODE);        // with this flag, GPS_set_next_wp will be called in the next loop -- OK with SERIAL GPS / OK with I2C GPS
            ENABLE_STATE(GPS_FIX_HOME);
            if (alt != 0)
                AltHold = alt;          // temporary implementation to test feature with apps
        } else if (wp_no == 16) {       // OK with SERIAL GPS  --  NOK for I2C GPS / needs more code dev in order to inject GPS coord inside I2C GPS
            GPS_hold[LAT] = lat;
            GPS_hold[LON] = lon;
            if (alt != 0)
                AltHold = alt;          // temporary implementation to test feature with apps
            nav_mode = NAV_MODE_WP;
            GPS_set_next_wp(&GPS_hold[LAT], &GPS_hold[LON]);
        }
        break;
#endif
    case MSP_SET_FEATURE:
        featureClearAll();
        featureSet(read32()); // features bitmap
        break;

    case MSP_SET_BOARD_ALIGNMENT:
        masterConfig.boardAlignment.rollDegrees = read16();
        masterConfig.boardAlignment.pitchDegrees = read16();
        masterConfig.boardAlignment.yawDegrees = read16();
        break;

    case MSP_SET_VOLTAGE_METER_CONFIG:
        masterConfig.batteryConfig.vbatscale = read8();           // actual vbatscale as intended
        masterConfig.batteryConfig.vbatmincellvoltage = read8();  // vbatlevel_warn1 in MWC2.3 GUI
        masterConfig.batteryConfig.vbatmaxcellvoltage = read8();  // vbatlevel_warn2 in MWC2.3 GUI
        masterConfig.batteryConfig.vbatwarningcellvoltage = read8();  // vbatlevel when buzzer starts to alert
        break;

    case MSP_SET_CURRENT_METER_CONFIG:
        masterConfig.batteryConfig.currentMeterScale = read16();
        masterConfig.batteryConfig.currentMeterOffset = read16();
        masterConfig.batteryConfig.currentMeterType = read8();
        masterConfig.batteryConfig.batteryCapacity = read16();
        break;

#ifndef USE_QUAD_MIXER_ONLY
    case MSP_SET_MIXER:
        masterConfig.mixerMode = read8();
        break;
#endif

    case MSP_SET_RX_CONFIG:
        masterConfig.rxConfig.serialrx_provider = read8();
        masterConfig.rxConfig.maxcheck = read16();
        masterConfig.rxConfig.midrc = read16();
        masterConfig.rxConfig.mincheck = read16();
        masterConfig.rxConfig.spektrum_sat_bind = read8();
        if (currentPort->dataSize > 8) {
            masterConfig.rxConfig.rx_min_usec = read16();
            masterConfig.rxConfig.rx_max_usec = read16();
        }
        break;

    case MSP_SET_FAILSAFE_CONFIG:
        masterConfig.failsafeConfig.failsafe_delay = read8();
        masterConfig.failsafeConfig.failsafe_off_delay = read8();
        masterConfig.failsafeConfig.failsafe_throttle = read16();
        break;

    case MSP_SET_RXFAIL_CONFIG:
        {
            uint8_t channelCount = currentPort->dataSize / 3;
            if (channelCount > MAX_SUPPORTED_RC_CHANNEL_COUNT) {
                headSerialError(0);
            } else {
                for (i = 0; i < channelCount; i++) {
                    masterConfig.rxConfig.failsafe_channel_configurations[i].mode = read8();
                    masterConfig.rxConfig.failsafe_channel_configurations[i].step = CHANNEL_VALUE_TO_RXFAIL_STEP(read16());
                }
            }
        }
        break;

    case MSP_SET_RSSI_CONFIG:
        masterConfig.rxConfig.rssi_channel = read8();
        break;

    case MSP_SET_RX_MAP:
        for (i = 0; i < MAX_MAPPABLE_RX_INPUTS; i++) {
            masterConfig.rxConfig.rcmap[i] = read8();
        }
        break;

    case MSP_SET_BF_CONFIG:

#ifdef USE_QUAD_MIXER_ONLY
        read8(); // mixerMode ignored
#else
        masterConfig.mixerMode = read8(); // mixerMode
#endif

        featureClearAll();
        featureSet(read32()); // features bitmap

        masterConfig.rxConfig.serialrx_provider = read8(); // serialrx_type

        masterConfig.boardAlignment.rollDegrees = read16(); // board_align_roll
        masterConfig.boardAlignment.pitchDegrees = read16(); // board_align_pitch
        masterConfig.boardAlignment.yawDegrees = read16(); // board_align_yaw

        masterConfig.batteryConfig.currentMeterScale = read16();
        masterConfig.batteryConfig.currentMeterOffset = read16();
        break;

    case MSP_SET_CF_SERIAL_CONFIG:
        {
            uint8_t portConfigSize = sizeof(uint8_t) + sizeof(uint16_t) + (sizeof(uint8_t) * 4);

            if (currentPort->dataSize % portConfigSize != 0) {
                headSerialError(0);
                break;
            }

            uint8_t remainingPortsInPacket = currentPort->dataSize / portConfigSize;

            while (remainingPortsInPacket--) {
                uint8_t identifier = read8();

                serialPortConfig_t *portConfig = serialFindPortConfiguration(identifier);
                if (!portConfig) {
                    headSerialError(0);
                    break;
                }

                portConfig->identifier = identifier;
                portConfig->functionMask = read16();
                portConfig->msp_baudrateIndex = read8();
                portConfig->gps_baudrateIndex = read8();
                portConfig->telemetry_baudrateIndex = read8();
                portConfig->blackbox_baudrateIndex = read8();
            }
        }
        break;

#ifdef LED_STRIP
    case MSP_SET_LED_COLORS:
        for (i = 0; i < CONFIGURABLE_COLOR_COUNT; i++) {
            hsvColor_t *color = &masterConfig.colors[i];
            color->h = read16();
            color->s = read8();
            color->v = read8();
        }
        break;

    case MSP_SET_LED_STRIP_CONFIG:
        {
            i = read8();
            if (i >= MAX_LED_STRIP_LENGTH || currentPort->dataSize != (1 + 7)) {
                headSerialError(0);
                break;
            }
            ledConfig_t *ledConfig = &masterConfig.ledConfigs[i];
            uint16_t mask;
            // currently we're storing directions and functions in a uint16 (flags)
            // the msp uses 2 x uint16_t to cater for future expansion
            mask = read16();
            ledConfig->flags = (mask << LED_DIRECTION_BIT_OFFSET) & LED_DIRECTION_MASK;

            mask = read16();
            ledConfig->flags |= (mask << LED_FUNCTION_BIT_OFFSET) & LED_FUNCTION_MASK;

            mask = read8();
            ledConfig->xy = CALCULATE_LED_X(mask);

            mask = read8();
            ledConfig->xy |= CALCULATE_LED_Y(mask);

            ledConfig->color = read8();

            reevalulateLedConfig();
        }
        break;
#endif
    case MSP_REBOOT:
        isRebootScheduled = true;
        break;

#ifdef USE_SERIAL_1WIRE
    case MSP_SET_1WIRE:
        // get channel number
        i = read8();
        // we do not give any data back, assume channel number is transmitted OK
        if (i == 0xFF) {
            // 0xFF -> preinitialize the Passthrough
            // switch all motor lines HI
            usb1WireInitialize();
            // and come back right afterwards
            // rem: App: Wait at least appx. 500 ms for BLHeli to jump into
            // bootloader mode before try to connect any ESC
        }
        else {
            // Check for channel number 0..ESC_COUNT-1
            if (i < ESC_COUNT) {
                // because we do not come back after calling usb1WirePassthrough
                // proceed with a success reply first
                headSerialReply(0);
                tailSerialReply();
                // wait for all data to send
                waitForSerialPortToFinishTransmitting(currentPort->port);
                // Start to activate here
                // motor 1 => index 0
                
                // search currentPort portIndex
                /* next lines seems to be unnecessary, because the currentPort always point to the same mspPorts[portIndex]
                uint8_t portIndex;	
				for (portIndex = 0; portIndex < MAX_MSP_PORT_COUNT; portIndex++) {
					if (currentPort == &mspPorts[portIndex]) {
						break;
					}
				}
				*/
                mspReleasePortIfAllocated(mspSerialPort); // CloseSerialPort also marks currentPort as UNUSED_PORT
                usb1WirePassthrough(i);
                // Wait a bit more to let App read the 0 byte and switch baudrate
                // 2ms will most likely do the job, but give some grace time
                delay(10);
                // rebuild/refill currentPort structure, does openSerialPort if marked UNUSED_PORT - used ports are skiped
                mspAllocateSerialPorts(&masterConfig.serialConfig);
                /* restore currentPort and mspSerialPort
                setCurrentPort(&mspPorts[portIndex]); // not needed same index will be restored
                */ 
                // former used MSP uart is active again
                // restore MSP_SET_1WIRE as current command for correct headSerialReply(0)
                currentPort->cmdMSP = MSP_SET_1WIRE;
            } else {
                // ESC channel higher than max. allowed
                // rem: BLHeliSuite will not support more than 8
                headSerialError(0);
            }
            // proceed as usual with MSP commands
            // and wait to switch to next channel
            // rem: App needs to call MSP_BOOT to deinitialize Passthrough
        }
        break;
#endif
    default:
        // we do not know how to handle the (valid) message, indicate error MSP $M!
        return false;
    }
