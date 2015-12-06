switch (currentPortState->cmdMSP) {
        case MSP_SET_RAW_RC:
            for (i = 0; i < 8; i++)
                rcData[i] = read16();
            headSerialReply(0);
            mspFrameRecieve();
            break;
        case MSP_SET_ACC_TRIM:
            cfg.angleTrim[PITCH] = read16();
            cfg.angleTrim[ROLL]  = read16();
            headSerialReply(0);
            break;
#ifdef GPS
        case MSP_SET_RAW_GPS:
            f.GPS_FIX = read8();
            GPS_numSat = read8();
            GPS_coord[LAT] = read32();
            GPS_coord[LON] = read32();
            GPS_altitude = read16();
            GPS_speed = read16();
            GPS_update |= 2;        // New data signalisation to GPS functions
            headSerialReply(0);
            break;
#endif
        case MSP_SET_PID:
            for (i = 0; i < PIDITEMS; i++) {
                cfg.P8[i] = read8();
                cfg.I8[i] = read8();
                cfg.D8[i] = read8();
            }
            headSerialReply(0);
            break;
        case MSP_SET_BOX:
            for (i = 0; i < numberBoxItems; i++)
                cfg.activate[availableBoxes[i]] = read16();
            headSerialReply(0);
            break;
        case MSP_SET_RC_TUNING:
            cfg.rcRate8 = read8();
            cfg.rcExpo8 = read8();
            read8(); // Legacy pitch-roll rate, read but not set.
            cfg.yawRate = read8();
            cfg.dynThrPID = read8();
            cfg.thrMid8 = read8();
            cfg.thrExpo8 = read8();
            headSerialReply(0);
            break;
        case MSP_SET_MISC:
            tmp = read16();
            // sanity check
            if (tmp < 1600 && tmp > 1400)
                mcfg.midrc = tmp;
            mcfg.minthrottle = read16();
            mcfg.maxthrottle = read16();
            mcfg.mincommand = read16();
            cfg.failsafe_throttle = read16();
            mcfg.gps_type = read8();
            mcfg.gps_baudrate = read8();
            mcfg.gps_ubx_sbas = read8();
            mcfg.multiwiicurrentoutput = read8();
            mcfg.rssi_aux_channel = read8();
            read8();
            cfg.mag_declination = read16() * 10;
            mcfg.vbatscale = read8();           // actual vbatscale as intended
            mcfg.vbatmincellvoltage = read8();  // vbatlevel_warn1 in MWC2.3 GUI
            mcfg.vbatmaxcellvoltage = read8();  // vbatlevel_warn2 in MWC2.3 GUI
            mcfg.vbatwarningcellvoltage = read8(); // vbatlevel when buzzer starts to alert
            headSerialReply(0);
            break;
        case MSP_SET_MOTOR:
            for (i = 0; i < 8; i++)
                motor_disarmed[i] = read16();
            headSerialReply(0);
            break;
        case MSP_SELECT_SETTING:
            if (!f.ARMED) {
                mcfg.current_profile = read8();
                if (mcfg.current_profile > 2)
                    mcfg.current_profile = 0;
                // this writes new profile index and re-reads it
                writeEEPROM(0, false);
            }
            headSerialReply(0);
            break;
        case MSP_SET_HEAD:
            magHold = read16();
            headSerialReply(0);
            break;
        case MSP_IDENT:
            headSerialReply(7);
            serialize8(VERSION);                    // multiwii version
            serialize8(mcfg.mixerConfiguration);    // type of multicopter
            serialize8(MSP_VERSION);                // MultiWii Serial Protocol Version
            serialize32(CAP_PLATFORM_32BIT | CAP_BASEFLIGHT_CONFIG | CAP_DYNBALANCE | CAP_FW_FLAPS); // "capability"
            break;
        case MSP_STATUS:
            headSerialReply(11);
            serialize16(cycleTime);
            serialize16(i2cGetErrorCounter());
            serialize16(sensors(SENSOR_ACC) | sensors(SENSOR_BARO) << 1 | sensors(SENSOR_MAG) << 2 | sensors(SENSOR_GPS) << 3 | sensors(SENSOR_SONAR) << 4);
            // OK, so you waste all the fucking time to have BOXNAMES and BOXINDEXES etc, and then you go ahead and serialize enabled shit simply by stuffing all
            // the bits in order, instead of setting the enabled bits based on BOXINDEX. WHERE IS THE FUCKING LOGIC IN THIS, FUCKWADS.
            // Serialize the boxes in the order we delivered them, until multiwii retards fix their shit
            junk = 0;
            tmp = f.ANGLE_MODE << BOXANGLE | f.HORIZON_MODE << BOXHORIZON |
                  f.BARO_MODE << BOXBARO | f.MAG_MODE << BOXMAG | f.HEADFREE_MODE << BOXHEADFREE | rcOptions[BOXHEADADJ] << BOXHEADADJ |
                  rcOptions[BOXCAMSTAB] << BOXCAMSTAB | rcOptions[BOXCAMTRIG] << BOXCAMTRIG |
                  f.GPS_HOME_MODE << BOXGPSHOME | f.GPS_HOLD_MODE << BOXGPSHOLD |
                  f.PASSTHRU_MODE << BOXPASSTHRU |
                  rcOptions[BOXBEEPERON] << BOXBEEPERON |
                  rcOptions[BOXLEDMAX] << BOXLEDMAX |
                  rcOptions[BOXLLIGHTS] << BOXLLIGHTS |
                  rcOptions[BOXVARIO] << BOXVARIO |
                  rcOptions[BOXCALIB] << BOXCALIB |
                  rcOptions[BOXGOV] << BOXGOV |
                  rcOptions[BOXOSD] << BOXOSD |
                  rcOptions[BOXTELEMETRY] << BOXTELEMETRY |
                  rcOptions[BOXSERVO1] << BOXSERVO1 |
                  rcOptions[BOXSERVO2] << BOXSERVO2 |
                  rcOptions[BOXSERVO3] << BOXSERVO3 |
                  f.ARMED << BOXARM;
            for (i = 0; i < numberBoxItems; i++) {
                int flag = (tmp & (1 << availableBoxes[i]));
                if (flag)
                    junk |= 1 << i;
            }
            serialize32(junk);
            serialize8(mcfg.current_profile);
            break;
        case MSP_RAW_IMU:
            headSerialReply(18);
            // Retarded hack until multiwiidorks start using real units for sensor data
            if (acc_1G > 1024) {
                for (i = 0; i < 3; i++)
                    serialize16(accSmooth[i] / 8);
            } else {
                for (i = 0; i < 3; i++)
                    serialize16(accSmooth[i]);
            }
            for (i = 0; i < 3; i++)
                serialize16(gyroData[i]);
            for (i = 0; i < 3; i++)
                serialize16(magADC[i]);
            break;
        case MSP_SERVO:
            s_struct((uint8_t *)&servo, 16);
            break;
        case MSP_SERVO_CONF:
            headSerialReply(MAX_SERVOS * 9);
            for (i = 0; i < MAX_SERVOS; i++) {
                serialize16(cfg.servoConf[i].min);
                serialize16(cfg.servoConf[i].max);
                serialize16(cfg.servoConf[i].middle);
                serialize8(cfg.servoConf[i].rate);
                serialize16(cfg.servoConf[i].direction);
            }
            break;
        case MSP_SET_SERVO_CONF:
            headSerialReply(0);
            for (i = 0; i < MAX_SERVOS; i++) {
                cfg.servoConf[i].min = read16();
                cfg.servoConf[i].max = read16();
                cfg.servoConf[i].middle = read16();
                cfg.servoConf[i].rate = read8();
                cfg.servoConf[i].direction = read16();
            }
            break;
        case MSP_SERVOMIX_CONF:
            headSerialReply(MAX_SERVO_RULES * sizeof(servoMixer_t));
            for (i = 0; i < MAX_SERVO_RULES; i++) {
                serialize8(mcfg.customServoMixer[i].targetChannel);
                serialize8(mcfg.customServoMixer[i].fromChannel);
                serialize8(mcfg.customServoMixer[i].rate);
                serialize8(mcfg.customServoMixer[i].speed);
                serialize8(mcfg.customServoMixer[i].min);
                serialize8(mcfg.customServoMixer[i].max);
                serialize8(mcfg.customServoMixer[i].box);
            }
            break;
        case MSP_SET_SERVOMIX_CONF:
            headSerialReply(0);
            for (i = 0; i < MAX_SERVO_RULES; i++) {
                mcfg.customServoMixer[i].targetChannel = read8();
                mcfg.customServoMixer[i].fromChannel = read8();
                mcfg.customServoMixer[i].rate = read8();
                mcfg.customServoMixer[i].speed = read8();
                mcfg.customServoMixer[i].min = read8();
                mcfg.customServoMixer[i].max = read8();
                mcfg.customServoMixer[i].box = read8();
            }
            loadCustomServoMixer();
            break;
        case MSP_FW_CONFIG:
            headSerialReply(38);
            serialize8(mcfg.fw_althold_dir);
            serialize16(cfg.fw_gps_maxcorr);
            serialize16(cfg.fw_gps_rudder);
            serialize16(cfg.fw_gps_maxclimb);
            serialize16(cfg.fw_gps_maxdive);
            serialize16(cfg.fw_climb_throttle);
            serialize16(cfg.fw_cruise_throttle);
            serialize16(cfg.fw_idle_throttle);
            serialize16(cfg.fw_scaler_throttle);
            serialize32(cfg.fw_roll_comp);
            serialize8(cfg.fw_rth_alt);
            // next added for future use
            serialize32(0);
            serialize32(0);
            serialize32(0);
            serialize32(0);
            break;
        case MSP_SET_FW_CONFIG:
            headSerialReply(0);
            mcfg.fw_althold_dir = read8();
            cfg.fw_gps_maxcorr = read16();
            cfg.fw_gps_rudder = read16();
            cfg.fw_gps_maxclimb = read16();
            cfg.fw_gps_maxdive = read16();
            cfg.fw_climb_throttle = read16();
            cfg.fw_cruise_throttle = read16();
            cfg.fw_idle_throttle = read16();
            cfg.fw_scaler_throttle = read16();
            cfg.fw_roll_comp = read32();
            cfg.fw_rth_alt = read8();
            // next added for future use
            read32();
            read32();
            read32();
            read32();
            break;
        case MSP_MOTOR:
            s_struct((uint8_t *)motor, 16);
            break;
        case MSP_RC:
            headSerialReply(16);
            for (i = 0; i < 8; i++)
                serialize16(rcData[i]);
            break;
#ifdef GPS
        case MSP_RAW_GPS:
            headSerialReply(16);
            serialize8(f.GPS_FIX);
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
#endif
        case MSP_ATTITUDE:
            headSerialReply(6);
            for (i = 0; i < 2; i++)
                serialize16(angle[i]);
            serialize16(heading);
            break;
        case MSP_ALTITUDE:
            headSerialReply(6);
            serialize32(EstAlt);
            serialize16(vario);
            break;
        case MSP_ANALOG:
            headSerialReply(7);
            serialize8((uint8_t)constrain(vbat, 0, 255));
            serialize16((uint16_t)constrain(mAhdrawn, 0, 0xFFFF)); // milliamphours drawn from battery
            serialize16(rssi);
            if (mcfg.multiwiicurrentoutput)
                serialize16((uint16_t)constrain((abs(amperage) * 10), 0, 0xFFFF)); // send amperage in 0.001 A steps
            else
                serialize16((uint16_t)constrain(abs(amperage), 0, 0xFFFF)); // send amperage in 0.01 A steps
            break;
        case MSP_RC_TUNING:
            headSerialReply(7);
            serialize8(cfg.rcRate8);
            serialize8(cfg.rcExpo8);
            serialize8(cfg.rollPitchRate[0]); // here for legacy support
            serialize8(cfg.yawRate);
            serialize8(cfg.dynThrPID);
            serialize8(cfg.thrMid8);
            serialize8(cfg.thrExpo8);
            break;
        case MSP_PID:
            headSerialReply(3 * PIDITEMS);
            for (i = 0; i < PIDITEMS; i++) {
                serialize8(cfg.P8[i]);
                serialize8(cfg.I8[i]);
                serialize8(cfg.D8[i]);
            }
            break;
        case MSP_PIDNAMES:
            headSerialReply(sizeof(pidnames) - 1);
            serializeNames(pidnames);
            break;
        case MSP_BOX:
            headSerialReply(2 * numberBoxItems);
            for (i = 0; i < numberBoxItems; i++)
                serialize16(cfg.activate[availableBoxes[i]]);
            break;
        case MSP_BOXNAMES:
            // headSerialReply(sizeof(boxnames) - 1);
            serializeBoxNamesReply();
            break;
        case MSP_BOXIDS:
            headSerialReply(numberBoxItems);
            for (i = 0; i < numberBoxItems; i++) {
                for  (j = 0; j < CHECKBOXITEMS; j++) {
                    if (boxes[j].permanentId == availableBoxes[i])
                        serialize8(boxes[j].permanentId);
                }
            }
            break;
        case MSP_MISC:
            headSerialReply(2 * 6 + 4 + 2 + 4);
            serialize16(mcfg.midrc);
            serialize16(mcfg.minthrottle);
            serialize16(mcfg.maxthrottle);
            serialize16(mcfg.mincommand);
            serialize16(cfg.failsafe_throttle);
            serialize8(mcfg.gps_type);
            serialize8(mcfg.gps_baudrate);
            serialize8(mcfg.gps_ubx_sbas);
            serialize8(mcfg.multiwiicurrentoutput);
            serialize8(mcfg.rssi_aux_channel);
            serialize8(0);
            serialize16(cfg.mag_declination / 10); // TODO check this shit
            serialize8(mcfg.vbatscale);
            serialize8(mcfg.vbatmincellvoltage);
            serialize8(mcfg.vbatmaxcellvoltage);
            serialize8(mcfg.vbatwarningcellvoltage);
            break;
        case MSP_MOTOR_PINS:
            headSerialReply(8);
            for (i = 0; i < 8; i++)
                serialize8(i + 1);
            break;
#ifdef GPS
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
                f.GPS_HOME_MODE = 0;        // with this flag, GPS_set_next_wp will be called in the next loop -- OK with SERIAL GPS / OK with I2C GPS
                f.GPS_FIX_HOME = 1;
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
            headSerialReply(0);
            break;
#endif /* GPS */
        case MSP_RESET_CONF:
            if (!f.ARMED)
                checkFirstTime(true);
            headSerialReply(0);
            break;
        case MSP_ACC_CALIBRATION:
            if (!f.ARMED)
                calibratingA = CALIBRATING_ACC_CYCLES;
            headSerialReply(0);
            break;
        case MSP_MAG_CALIBRATION:
            if (!f.ARMED)
                f.CALIBRATE_MAG = 1;
            headSerialReply(0);
            break;
        case MSP_EEPROM_WRITE:
            if (f.ARMED) {
                headSerialError(0);
            } else {
                writeEEPROM(0, true);
                headSerialReply(0);
            }
            break;
        case MSP_DEBUG:
            headSerialReply(8);
            // make use of this crap, output some useful QA statistics
            debug[3] = ((hse_value / 1000000) * 1000) + (SystemCoreClock / 1000000);         // XX0YY [crystal clock : core clock]
            for (i = 0; i < 4; i++)
                serialize16(debug[i]);      // 4 variables are here for general monitoring purpose
            break;

        // Additional commands that are not compatible with MultiWii
        case MSP_ACC_TRIM:
            headSerialReply(4);
            serialize16(cfg.angleTrim[PITCH]);
            serialize16(cfg.angleTrim[ROLL]);
            break;
        case MSP_UID:
            headSerialReply(12);
            serialize32(U_ID_0);
            serialize32(U_ID_1);
            serialize32(U_ID_2);
            break;
#ifdef GPS
        case MSP_GPSSVINFO:
            headSerialReply(1 + (GPS_numCh * 4));
            serialize8(GPS_numCh);
            for (i = 0; i < GPS_numCh; i++) {
                serialize8(GPS_svinfo_chn[i]);
                serialize8(GPS_svinfo_svid[i]);
                serialize8(GPS_svinfo_quality[i]);
                serialize8(GPS_svinfo_cno[i]);
            }
            // Poll new SVINFO from GPS
            gpsPollSvinfo();
            break;
        case MSP_GPSDEBUGINFO:
            headSerialReply(16);
            if (sensors(SENSOR_GPS)) {
                serialize32(GPS_update_rate[1] - GPS_update_rate[0]);
                serialize32(GPS_svinfo_rate[1] - GPS_svinfo_rate[0]);
            } else {
                serialize32(0);
                serialize32(0);
            }
            serialize32(GPS_HorizontalAcc);
            serialize32(GPS_VerticalAcc);
            break;
#endif /* GPS */

        case MSP_SET_CONFIG:
            headSerialReply(0);
            mcfg.mixerConfiguration = read8(); // multitype
            featureClearAll();
            featureSet(read32()); // features bitmap
            mcfg.serialrx_type = read8(); // serialrx_type
            mcfg.board_align_roll = read16(); // board_align_roll
            mcfg.board_align_pitch = read16(); // board_align_pitch
            mcfg.board_align_yaw = read16(); // board_align_yaw
            mcfg.currentscale = read16();
            mcfg.currentoffset = read16();
            mcfg.motor_pwm_rate = read16();
            cfg.rollPitchRate[0] = read8();
            cfg.rollPitchRate[1] = read8();
            mcfg.power_adc_channel = read8();
            cfg.small_angle = read8();
            mcfg.looptime = read16();
            cfg.locked_in = read8();
            /// ???
            break;
        case MSP_CONFIG:
            headSerialReply(1 + 4 + 1 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 1 + 1 + 2 + 1);
            serialize8(mcfg.mixerConfiguration);
            serialize32(featureMask());
            serialize8(mcfg.serialrx_type);
            serialize16(mcfg.board_align_roll);
            serialize16(mcfg.board_align_pitch);
            serialize16(mcfg.board_align_yaw);
            serialize16(mcfg.currentscale);
            serialize16(mcfg.currentoffset);
            serialize16(mcfg.motor_pwm_rate);
            serialize8(cfg.rollPitchRate[0]);
            serialize8(cfg.rollPitchRate[1]);
            serialize8(mcfg.power_adc_channel);
            serialize8(cfg.small_angle);
            serialize16(mcfg.looptime);
            serialize8(cfg.locked_in);
            /// ???
            break;

        case MSP_RCMAP:
            headSerialReply(MAX_INPUTS); // TODO fix this
            for (i = 0; i < MAX_INPUTS; i++)
                serialize8(mcfg.rcmap[i]);
            break;
        case MSP_SET_RCMAP:
            headSerialReply(0);
            for (i = 0; i < MAX_INPUTS; i++)
                mcfg.rcmap[i] = read8();
            break;

        case MSP_REBOOT:
            headSerialReply(0);
            pendReboot = true;
            break;

        case MSP_BUILDINFO:
            headSerialReply(11 + 4 + 4);
            for (i = 0; i < 11; i++)
                serialize8(build[i]); // MMM DD YYYY as ascii, MMM = Jan/Feb... etc
            serialize32(0); // future exp
            serialize32(0); // future exp
            break;

        default:                   // we do not know how to handle the (valid) message, indicate error MSP $M!
            headSerialError(0);
            break;
    }
