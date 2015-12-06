switch (blackboxState) {
        case BLACKBOX_STATE_SEND_HEADER:
            //On entry of this state, xmitState.headerIndex is 0 and startTime is intialised

            /*
             * Once the UART has had time to init, transmit the header in chunks so we don't overflow its transmit
             * buffer, overflow the OpenLog's buffer, or keep the main loop busy for too long.
             */
            if (millis() > xmitState.u.startTime + 100) {
                if (blackboxDeviceReserveBufferSpace(BLACKBOX_TARGET_HEADER_BUDGET_PER_ITERATION) == BLACKBOX_RESERVE_SUCCESS) {
                    for (i = 0; i < BLACKBOX_TARGET_HEADER_BUDGET_PER_ITERATION && blackboxHeader[xmitState.headerIndex] != '\0'; i++, xmitState.headerIndex++) {
                        blackboxWrite(blackboxHeader[xmitState.headerIndex]);
                        blackboxHeaderBudget--;
                    }

                    if (blackboxHeader[xmitState.headerIndex] == '\0') {
                        blackboxSetState(BLACKBOX_STATE_SEND_MAIN_FIELD_HEADER);
                    }
                }
            }
        break;
        case BLACKBOX_STATE_SEND_MAIN_FIELD_HEADER:
            //On entry of this state, xmitState.headerIndex is 0 and xmitState.u.fieldIndex is -1
            if (!sendFieldDefinition('I', 'P', blackboxMainFields, blackboxMainFields + 1, ARRAY_LENGTH(blackboxMainFields),
                    &blackboxMainFields[0].condition, &blackboxMainFields[1].condition)) {
#ifdef GPS
                if (feature(FEATURE_GPS)) {
                    blackboxSetState(BLACKBOX_STATE_SEND_GPS_H_HEADER);
                } else
#endif
                    blackboxSetState(BLACKBOX_STATE_SEND_SLOW_HEADER);
            }
        break;
#ifdef GPS
        case BLACKBOX_STATE_SEND_GPS_H_HEADER:
            //On entry of this state, xmitState.headerIndex is 0 and xmitState.u.fieldIndex is -1
            if (!sendFieldDefinition('H', 0, blackboxGpsHFields, blackboxGpsHFields + 1, ARRAY_LENGTH(blackboxGpsHFields),
                    NULL, NULL)) {
                blackboxSetState(BLACKBOX_STATE_SEND_GPS_G_HEADER);
            }
        break;
        case BLACKBOX_STATE_SEND_GPS_G_HEADER:
            //On entry of this state, xmitState.headerIndex is 0 and xmitState.u.fieldIndex is -1
            if (!sendFieldDefinition('G', 0, blackboxGpsGFields, blackboxGpsGFields + 1, ARRAY_LENGTH(blackboxGpsGFields),
                    &blackboxGpsGFields[0].condition, &blackboxGpsGFields[1].condition)) {
                blackboxSetState(BLACKBOX_STATE_SEND_SLOW_HEADER);
            }
        break;
#endif
        case BLACKBOX_STATE_SEND_SLOW_HEADER:
            //On entry of this state, xmitState.headerIndex is 0 and xmitState.u.fieldIndex is -1
            if (!sendFieldDefinition('S', 0, blackboxSlowFields, blackboxSlowFields + 1, ARRAY_LENGTH(blackboxSlowFields),
                    NULL, NULL)) {
                blackboxSetState(BLACKBOX_STATE_SEND_SYSINFO);
            }
        break;
        case BLACKBOX_STATE_SEND_SYSINFO:
            //On entry of this state, xmitState.headerIndex is 0

            //Keep writing chunks of the system info headers until it returns true to signal completion
            if (blackboxWriteSysinfo()) {

                /*
                 * Wait for header buffers to drain completely before data logging begins to ensure reliable header delivery
                 * (overflowing circular buffers causes all data to be discarded, so the first few logged iterations
                 * could wipe out the end of the header if we weren't careful)
                 */
                if (blackboxDeviceFlush()) {
                    blackboxSetState(BLACKBOX_STATE_RUNNING);
                }
            }
        break;
        case BLACKBOX_STATE_PAUSED:
            // Only allow resume to occur during an I-frame iteration, so that we have an "I" base to work from
            if (IS_RC_MODE_ACTIVE(BOXBLACKBOX) && blackboxShouldLogIFrame()) {
                // Write a log entry so the decoder is aware that our large time/iteration skip is intended
                flightLogEvent_loggingResume_t resume;

                resume.logIteration = blackboxIteration;
                resume.currentTime = currentTime;

                blackboxLogEvent(FLIGHT_LOG_EVENT_LOGGING_RESUME, (flightLogEventData_t *) &resume);
                blackboxSetState(BLACKBOX_STATE_RUNNING);
                
                blackboxLogIteration();
            }

            // Keep the logging timers ticking so our log iteration continues to advance
            blackboxAdvanceIterationTimers();
        break;
        case BLACKBOX_STATE_RUNNING:
            // On entry to this state, blackboxIteration, blackboxPFrameIndex and blackboxIFrameIndex are reset to 0
            if (blackboxModeActivationConditionPresent && !IS_RC_MODE_ACTIVE(BOXBLACKBOX)) {
                blackboxSetState(BLACKBOX_STATE_PAUSED);
            } else {
                blackboxLogIteration();
            }

            blackboxAdvanceIterationTimers();
        break;
        case BLACKBOX_STATE_SHUTTING_DOWN:
            //On entry of this state, startTime is set and a flush is performed

            /*
             * Wait for the log we've transmitted to make its way to the logger before we release the serial port,
             * since releasing the port clears the Tx buffer.
             *
             * Don't wait longer than it could possibly take if something funky happens.
             */
            if (millis() > xmitState.u.startTime + BLACKBOX_SHUTDOWN_TIMEOUT_MILLIS || blackboxDeviceFlush()) {
                blackboxDeviceClose();
                blackboxSetState(BLACKBOX_STATE_STOPPED);
            }
        break;
        default:
        break;
    }
